/*
	Vantage-Point Tree
	Author: Leonid Kanteev 
	github.com/lkolt
*/

#include "Vantage-Point tree.h"
#include <ctime>

const int num_points = 1e5;
const int num_queries = 1e4;

struct Point {
	double latitude;
	double longitude;

	double dist(const Point& p2) {
		double a = (latitude - p2.latitude);
		double b = (longitude - p2.longitude);
		return sqrt(a*a + b*b);
	}
};

using namespace std;

int main() {
	std::vector<Point> points;
	std::vector<Point> queries;

	while (points.size() < num_points) {
		Point point;
		point.latitude = rand();
		point.longitude = rand();
		points.push_back(point);
	}

	while (queries.size() < num_queries) {
		Point point;
		point.latitude = rand();
		point.longitude = rand();
		queries.push_back(point);
	}

	unsigned int build_start_time = clock();

	VpTree<Point> tree;
	tree.create(points);

	unsigned int build_end_time = clock(); 
	double build_time = (double)(build_end_time - build_start_time) / CLOCKS_PER_SEC; 

	cout << "Building done, time: " << build_time << endl;
	
	unsigned int search_start_time = clock();

	for (int i = 0; i < queries.size(); i++) {
		std::vector<Point> results;
		std::vector<double> distances;
		tree.search(queries[i], 8, &results, &distances);
	}

	unsigned int search_end_time = clock();
	double search_time = (double)(search_end_time - search_start_time) / CLOCKS_PER_SEC;

	cout << "Searching done, time: " << search_time << endl;


	cout << "------------" << endl;

	unsigned int insert_start_time = clock();

	VpTree<Point> ntree;
	for (int i = 0; i < points.size(); i++) {
		ntree.insert(points[i]);
	}

	unsigned int insert_end_time = clock();
	double insert_time = (double)(insert_end_time - insert_start_time) / CLOCKS_PER_SEC;

	cout << "Inserting done, time: " << insert_time << endl;

	unsigned int nsearch_start_time = clock();

	for (int i = 0; i < queries.size(); i++) {
		std::vector<Point> results;
		std::vector<double> distances;
		ntree.search(queries[i], 8, &results, &distances);
	}

	unsigned int nsearch_end_time = clock();
	double nsearch_time = (double)(nsearch_end_time - nsearch_start_time) / CLOCKS_PER_SEC;

	cout << "Searching in inserted tree done, time: " << nsearch_time << endl;

	return 0;
}