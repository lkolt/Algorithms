#include <bits/stdc++.h>

#define pii pair <int, int>
#define pll pair <ll, ll>
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define REP(i, n, m) for (int i = (int)n; i < (int)m; i++)
#define prep(i, n) for (int i = 1; i <= (int)n; i++)
#define per(i, n) for (int i = n; i >= 0; i--)
#define pb push_back
#define vi vector <int>
#define vl vector <ll>
#define fi first
#define se second
#define mp make_pair

typedef long long ll;
typedef long double ld;


using namespace std;

//------------------------ read

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x );
inline void writeWord( const char *s );

//----------------------- const

const int maxn = (1.6e5);
const ll INF = (1e18) + 7;
const ld EPS = 1e-8;

//----------------------- main

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
    if (left != right) {
        left = get_ancestor(left);
        right = get_ancestor(right);

        if (rate[right] > rate[left]) {
            rate[right]++;
            ancestor[left] = right;
        } else {
            rate[left]++;
            ancestor[right] = left;
        }
    }
}

// graph

vi edges[maxn];
vector <pair <pii, bool>> list_edges;
vi removed_vers;
bool was[maxn];

void dfs (int v, int color) {
    unite(v, color);
    was[v] = true;
    for (auto u: edges[v]) {
        if (!was[u]) {
            dfs(u, color);
        }
    }
}

// other
int ans[maxn];

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        ancestor[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        list_edges.push_back({{x, y}, false});
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        removed_vers.push_back(x);
        list_edges[x - 1].second = true;
    }

    for (auto edge: list_edges) {
        if (!edge.second) {
            int v = edge.first.first;
            int u = edge.first.second;
            edges[v].pb(u);
            edges[u].pb(v);
        }
    }

    int final_ans = 0;
    for (int v = 1; v <= n; v++) {
        if (!was[v]) {
            dfs(v, v);
            final_ans++;
        }
    }

    while (!removed_vers.empty()) {
        int num_edge = removed_vers.back();
        int v = get_ancestor(list_edges[num_edge - 1].first.first);
        int u = get_ancestor(list_edges[num_edge - 1].first.second);
        removed_vers.pop_back();
        ans[removed_vers.size()] = final_ans;
        final_ans -= u != v;
        unite(v, u);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << " ";
    }

	return 0;
}

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
