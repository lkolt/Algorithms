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

ll ans[maxn];

// DSU

int rate[maxn];
int ancestor[maxn];

int get_ancestor (int ver) {
    if (ancestor[ver] == ver) {
        return ver;
    }
    return ancestor[ver] = get_ancestor(ancestor[ver]);
}

void unite(int left, int right) {
    ancestor[left] = right;
}

// graph
vector <pii> edges[maxn];
vector <pii> marks[maxn];
ll sum[maxn];
set <int> was;

void get_sum (int v, int pred, ll sum_pred) {
    sum[v] = sum_pred;
    for (auto u: edges[v]) {
        if (u.first != pred) {
            get_sum(u.first, v, sum_pred + u.second);
        }
    }
}

void dfs (int v, int pred) {
    was.insert(v);
    for (auto mark: marks[v]) {
        if (was.count(mark.first)) {
            int anc = get_ancestor(mark.first);
            ans[mark.second] = sum[mark.first] + sum[v] - 2 * sum[anc];
        }
    }

    for (auto u: edges[v]) {
        if (u.first != pred) {
            dfs(u.first, v);
            unite(u.first, v);
        }
    }
}

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ancestor[i] = i;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }


    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        if (x == y) {
            ans[i] = 0;
        } else {
            marks[x].push_back({y, i});
            marks[y].push_back({x, i});
        }
    }

    // calc sum
    get_sum(0, -1, 0);
    // calc ans
    dfs(0, -1);

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

	return 0;
}

/**
tests:
8
0 1 1
0 2 2
1 5 5
1 4 4
5 6 6
5 7 7
2 3 3
5
1 2
6 1
6 4
6 3
7 4

*/

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
