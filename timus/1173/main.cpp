/**
    Author: Leonid Kanteev (@lkolt)
    Github: github.com/lkolt/
*/

#include <bits/stdc++.h>
#include <string>

/** Template */

#define pii pair <int, int>
#define pll pair <ll, ll>
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define pb push_back
#define vi vector <int>
#define vl vector <ll>

typedef long long ll;
typedef long double ld;

using namespace std;

/** IO Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x );
inline void writeWord( const char *s );

/** Const */

const int maxn = (1.6e5);
const ll INF = (1e18) + 7;
const ld EPS = 1e-8;

/** Solution */

struct point {
    double x;
    double y;
    int idx;
    double angle;

    inline bool operator < (const point &pt) const {
        return (y < pt.y || (y == pt.y && x < pt.x));
    }

    inline bool operator > (const point &pt) const {
        return (y > pt.y || (y == pt.y && x > pt.x));
    }

    inline bool operator << (const point &pt) const {
        return (y < pt.y || (y == pt.y && x > pt.x));
    }

    inline bool operator >> (const point &pt) const {
        return (y > pt.y || (y == pt.y && x < pt.x));
    }

    inline double get_angle(const point &pt) {
        return atan2((double)(y - pt.y), (double)(x - pt.x));
    }

    bool less(const point &pt) const {
        return angle < pt.angle || (angle == pt.angle && (*this < pt));
    }

    bool more(const point &pt) const {
        return angle < pt.angle || (angle == pt.angle && (*this > pt));
    }

    void print() const {
        cout << "x: " << x << ", y: " << y << ", idx: " << idx << ", angle: " << angle << endl;
    }
};

vector <point> solve() {
    vector <point> path;
    point first;
    cin >> first.x >> first.y;
    first.idx = 0;
    path.push_back(first);

    int n;
    cin >> n;

    point min_point = {100001, 100001, -1};
    rep(i, n) {
        double x, y;
        int idx;
        cin >> x >> y >> idx;
        point new_point = point({x, y, idx});
        path.push_back(new_point);
    }

    for (auto pt: path) {
        if (pt << min_point) {
            min_point = pt;
        }
    }

    vector <point> ans;
    rep(i, path.size()) {
        path[i].angle = path[i].get_angle(min_point);
    }

    sort(path.begin(), path.end(), [](const point& a, const point& b) {
        return a.less(b);
    });
/*
    for (auto pt: path) {
        pt.print();
    }
*/
    int first_pump_idx = -1;
    rep(i, path.size()) {
        if (path[i].idx == 0) {
            first_pump_idx = i;
        }
        if (first_pump_idx > -1) {
            ans.push_back(path[i]);
        }
    }
    rep(i, first_pump_idx) {
        ans.push_back(path[i]);
    }

    return ans;
}

int main()
{
    //freopen("in_new.txt", "r", stdin);   // Uncomment for multitest
    //freopen("out.txt", "w", stdout); // Uncomment for multitest
  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);


    int p = 1;
    //cin >> p; // Uncomment for multitest

    rep (i, p) {
        vector <point> ans = solve();
        for (auto pt: ans) {
            cout << pt.idx << endl;
        }
        cout << 0 << endl;
    }

	return 0;
}

/** Helpful funcs*/
/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T>
inline void writeInt( T x, char end ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;
