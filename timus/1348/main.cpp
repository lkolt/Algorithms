/**
    Author: Leonid Kanteev (@lkolt)
    Github: github.com/lkolt/
*/


#include <bits/stdc++.h>

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

long double sqr(long double a) {
    return a * a;
}

struct point {
    long double x;
    long double y;

    long double dist(point pt) {
        return sqrt(sqr(x - pt.x) + sqr(y - pt.y));
    }

    friend istream &operator>>(istream &input, point &pt) { 
        input >> pt.x >> pt.y;
        return input;            
    }

    friend ostream &operator<<(ostream &output, point &pt) { 
        output << "x : " << pt.x << " y : " << pt.y << endl;
        return output;            
    }
};

struct line {
    long double a, b, c;

    line(point pt1, point pt2) {
        a = pt1.y - pt2.y;
        b = pt2.x - pt1.x;
        c = pt1.x * pt2.y - pt2.x * pt1.y;
    }

    point get_height(point pt) {
        long double denominator = sqr(a) + sqr(b);
        long double x = b * (b * pt.x - a * pt.y) - a * c;
        long double y = a * (a * pt.y - b * pt.x) - b * c;
        return {x / denominator, y / denominator};
    }

    long double get_value(point pt) {
        return a * pt.x + b * pt.y + c;
    }
};

int get_sign(long double val) {
    if (abs(val) < 1e-4) {
        return 0;
    }
    return val < 0 ? -1 : 1;
}

point get_randon_point() {
    srand(unsigned(time(0)));
    return {(long double)rand(), (long double)rand()};
}

void solve() {
    point a, b, c;
    long double l;
    cin >> a >> b >> c >> l;

    auto format_value = [l](long double dist) { // lambda for simplify output
        return max(dist - l, (long double)0.0);
    };

    line ab = line(a, b);    
    long double a_dist = c.dist(a);
    long double b_dist = c.dist(b);
    long double long_dist = max(a_dist, b_dist);
    long double short_dist = min(a_dist, b_dist);

    point height = ab.get_height(c);
    long double h_dist = c.dist(height);

    point random = get_randon_point();         // get random point for make lines to a and b
    line ar = line(a, random);                 // random point not on ab line
    line br = line(b, random);

    long double h_ar = ar.get_value(height);
    long double h_br = br.get_value(height);
    if (get_sign(h_ar) == get_sign(h_br)) {    // height outside ab interval 
        h_dist = short_dist;                   // just take min(ac, bc)
    }

    cout << format_value(h_dist) << endl;
    cout << format_value(long_dist);
}

int main()
{
    // freopen("in.txt", "r", stdin);          // some interesting tests (WA 7 and WA 25)
    // freopen("", "w", stdout);

    cout << fixed << setprecision(2);

    ios_base::sync_with_stdio(false);

    solve();

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
