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

const int maxn = 32;
const ll INF = (1e18) + 7;
const ld EPS = 1e-8;

/** Solution */

vector <int> k;
vector <vector <pair <int, int>>> e[maxn];
vector <long long> ans[maxn];

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    ans[0].push_back(0);
    k.push_back(1);

    for (int i = 1; i <= n; i++) {
        int k_i;
        cin >> k_i;
        k.push_back(k_i);
        for (int j = 0; j < k_i; j++) {
            e[i].push_back({});
            ans[i].push_back({});
            while (true) {
                long long from, price;
                cin >> from;
                if (from == 0) {
                    break;
                }
                cin >> price;
                e[i][j].push_back({from - 1, price});
            }
        }
        if (i <= n - 1) {
            char unused;
            cin >> unused;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k[i]; j++) {
            ans[i][j] = INF; // bicycle
            for (int v = 0; v < e[i][j].size(); v++) {
                int from = e[i][j][v].first;
                long long price = e[i][j][v].second;
                ans[i][j] = min(ans[i][j], ans[i - 1][from] + price);
            }
        }
    }

    long long res = INF;
    for (int i = 0; i < k[n]; i++) {
        res = min(res, ans[n][i]);
    }

    cout << res;

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
