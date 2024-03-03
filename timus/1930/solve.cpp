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

vi forw[maxn];
vi rev[maxn];

set<int> cur[maxn];
bool was[maxn];

/** Solution */

int solution(int n, int from, int to, vi *fw, vi *rv) {
	cur[0].insert(from);

	int ans = -1;
    for (int i = 0; i < n; i++) {
		while (cur[i].size() > 0) {
			int v = *cur[i].begin();
			cur[i].erase(v);
			if (was[v]) {
				continue;
			}
			was[v] = true;
			// cout << v << " " << i << endl;
			if (v == to) {
				ans = i;
				break;
			}
			for (int j = 0; j < fw[v].size(); j++) {
				int t = fw[v][j];
				int gear_change = (i) % 2;
				if (!was[t]) {
					cur[i + gear_change].insert(t);
				}
			}
			for (int j = 0; j < rv[v].size(); j++) {
				int t = rv[v][j];
				int gear_change = (i + 1) % 2;
				if (!was[t]) {
					cur[i + gear_change].insert(t);
				}
			}
		}
    }

	return ans;
}

int main()
{
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);

    int n = readInt();
    int m = readInt();

    for (int i = 0; i < m; i++) {
        int _from = readInt() - 1;
        int _to = readInt() - 1;

		forw[_from].push_back(_to);
		rev[_to].push_back(_from);
    }

	int from = readInt() - 1;
	int to = readInt() - 1;

	int ans = solution(n, from, to, forw, rev);
	// cout << "first " << ans << endl; 

	for (int i = 0; i < n; i++) {
		was[i] = false;
		cur[i].clear();
	}
	
	ans = min(solution(n, from, to, rev, forw), ans);

	cout << ans;

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
