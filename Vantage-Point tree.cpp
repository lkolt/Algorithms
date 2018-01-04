/*
	Vantage-Point Tree
	Author: Leonid Kanteev 
	github.com/lkolt
*/

#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <limits>

template<typename T, double(*distance)(const T&, const T&)>
class VpTree {
	public:
		VpTree() : _root(0) {}

		~VpTree() {
			delete _root;
		}

		void create(const std::vector<T> & items) {
			delete _root;
			_items = items;
			_root = buildFromPoints(0, items.size());
		}

		void insert(const T newItem) {
			_items.push_back(newItem);
			count_inserts++;
			if (count_inserts > NUMBER_OF_INSERTS_TO_REBUILD) {
				count_inserts = 0;
				create(_items);
				return;
			}
			_root = insert_(_root, { newItem, _items.size() - 1 });
		}

		void search(const T& target, int k, std::vector<T>* results, std::vector<double>* distances) {
			std::priority_queue<HeapItem> heap;

			_tau = std::numeric_limits<double>::max();
			search_(_root, target, k, heap);

			results->clear(); distances->clear();

			while (!heap.empty()) {
				results->push_back(_items[heap.top().index]);
				distances->push_back(heap.top().dist);
				heap.pop();
			}

			std::reverse(results->begin(), results->end());
			std::reverse(distances->begin(), distances->end());
		}

	private:
		std::vector<T> _items;
		double _tau;
		int count_inserts = 0;
		const int NUMBER_ITEMS_IN_LEAF = 10;
		const int NUMBER_OF_INSERTS_TO_REBUILD = 2e5;

		struct Node {
			int index;
			double threshold;
			Node* left;
			Node* right;
			bool isLeaf;
			std::vector <std::pair<T, int> > leafItems;

			Node() :
				index(0), threshold(0.), left(0), right(0), isLeaf(false) {}

			~Node() {
				delete left;
				delete right;
			}
		}*_root;

		struct HeapItem {
			HeapItem(int index, double dist) : index(index), dist(dist) {}
			int index;
			double dist;
			bool operator<(const HeapItem& o) const {
				return dist < o.dist;
			}
		};

		struct DistanceComparator {
			const T& item;
			DistanceComparator(const T& item) : item(item) {}
			bool operator()(const T& a, const T& b) {
				return distance(item, a) < distance(item, b);
			}
		};

		Node* insert_(Node *node, std::pair<T, int> newItem) {
			if (node == NULL) {
				Node* newNode = new Node();
				newNode->isLeaf = true;
				newNode->leafItems.clear();
				newNode->leafItems.push_back(newItem);
				return newNode;
			}

			if (node->isLeaf == true) {
				node->leafItems.push_back(newItem);
				if (node->leafItems.size() == NUMBER_ITEMS_IN_LEAF) {
					Node *newNode = new Node();
					int index = node->leafItems[rand() % node->leafItems.size()].second;
					newNode->index = index;
					sort(node->leafItems.begin(), node->leafItems.end(), 
						[&](std::pair<T, int> a, std::pair<T, int> b) {
							return (distance(_items[index], a.first) < distance(_items[index], b.first)); 
					});

					int size = node->leafItems.size();

					newNode->threshold = (distance(_items[index], node->leafItems[size / 2].first));

					Node *leftNode = new Node();
					leftNode->isLeaf = true;
					leftNode->leafItems.clear();
					for (int i = 0; i < size / 2; i++) {
						leftNode->leafItems.push_back(node->leafItems[i]);
					}

					Node *rightNode = new Node();
					rightNode->isLeaf = true;
					rightNode->leafItems.clear();
					for (int i = size / 2; i < size; i++) {
						rightNode->leafItems.push_back(node->leafItems[i]);
					}

					newNode->left = leftNode;
					newNode->right = rightNode;
					delete(node);  
					return newNode;
				} 
				return node;
			}

			
			double dist = distance(_items[node->index], newItem.first);
			if (dist < node->threshold) {
				node->left = insert_(node->left, newItem);
			} else {
				node->right = insert_(node->right, newItem);
			}

			return node;
		}

		Node* buildFromPoints(int lower, int upper) {
			if (upper == lower) {
				return NULL;
			}

			Node* node = new Node();
			node->index = lower;

			if (upper - lower > NUMBER_ITEMS_IN_LEAF) {

				int i = (int)((double)rand() / RAND_MAX * (upper - lower - 1)) + lower;
				std::swap(_items[lower], _items[i]);

				int median = (upper + lower) / 2;

				std::nth_element(
					_items.begin() + lower + 1,
					_items.begin() + median,
					_items.begin() + upper,
					DistanceComparator(_items[lower]));

				node->threshold = distance(_items[lower], _items[median]);

				node->index = lower;
				node->left = buildFromPoints(lower + 1, median);
				node->right = buildFromPoints(median, upper);
			}
			else {
				node->isLeaf = true;
				node->leafItems.clear();
				for (int i = lower; i < upper; i++) {
					node->leafItems.push_back({ _items[i], i });
				}
				
			}

			return node;
		}

		void search_(Node* node, const T& target, int k, std::priority_queue<HeapItem>& heap) {
			if (node == NULL) return;

			if (node->isLeaf) {
				for (int i = 0; i < node->leafItems.size(); i++) {
					double dist = distance(node->leafItems[i].first, target);

					if (dist < _tau) {
						if (heap.size() == k) heap.pop();
						heap.push(HeapItem(node->leafItems[i].second, dist));
						if (heap.size() == k) _tau = heap.top().dist;
					}
				}

				return;
			}

			double dist = distance(_items[node->index], target);

			if (dist < _tau) {
				if (heap.size() == k) heap.pop();
				heap.push(HeapItem(node->index, dist));
				if (heap.size() == k) _tau = heap.top().dist;
			}

			if (node->left == NULL && node->right == NULL) {
				return;
			}

			if (dist < node->threshold) {
				if (dist - _tau <= node->threshold) {
					search_(node->left, target, k, heap);
				}

				if (dist + _tau >= node->threshold) {
					search_(node->right, target, k, heap);
				}

			}
			else {
				if (dist + _tau >= node->threshold) {
					search_(node->right, target, k, heap);
				}

				if (dist - _tau <= node->threshold) {
					search_(node->left, target, k, heap);
				}
			}
		}
};


struct Point {
	double latitude;
	double longitude;
};

double distance(const Point& p1, const Point& p2) {
	double a = (p1.latitude - p2.latitude);
	double b = (p1.longitude - p2.longitude);
	return sqrt(a*a + b*b);
}

using namespace std;

int main() {
	std::vector<Point> points;
	while (points.size() < 1e5) {
		Point point;
		point.latitude = rand();
		point.longitude = rand();
		//cout << point.latitude << " " << point.longitude << endl;
		points.push_back(point);
	}

	VpTree<Point, distance> tree;

	tree.create(points);
	cout << "Done" << endl;
	
	Point point;
	point.latitude = 43.466438;
	point.longitude = -80.519185;
	std::vector<Point> results;
	std::vector<double> distances;

	tree.search(point, 8, &results, &distances);

	for (int i = 0; i < results.size(); i++) {
		cout << results[i].latitude << " " << results[i].longitude << " " << distances[i] << endl;
	}

	cout << "------------" << endl;

	VpTree<Point, distance> ntree;

	for (int i = 0; i < points.size(); i++) {
		ntree.insert(points[i]);
	}

	cout << "Done" << endl;

	results.clear();
	distances.clear();

	ntree.search(point, 8, &results, &distances);

	for (int i = 0; i < results.size(); i++) {
		cout << results[i].latitude << " " << results[i].longitude << " " << distances[i] << endl;
	}


	int k;
	cin >> k;

	return 0;
}