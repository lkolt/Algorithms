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

//----------------------- const

const int maxn = (1.6e7);
const ll INF = (1e18) + 7;
const ld EPS = 1e-8;

//----------------------- main

ll get_lines(ll n) {
    return 2 * n - 2;
}

ll get_diags(ll n, ll a, ll b) {
    ll res = 0;
    res += a < b ? a - 1 : b - 1;
    res += a - 1 < n - b ? a - 1 : n - b;
    res += n - a < b - 1 ? n - a : b - 1;
    res += n - a < n - b ? n - a : n - b;
    return res;
}

ll get_move(ll n, ll x, ll y, vi move_x, vi move_y) {
    int ans = 0;
    for (int i = 0; i < move_x.size(); i++) {
        ll x_new = move_x[i] + x;
        ll y_new = move_y[i] + y;
        if (x_new <= n && x_new > 0 &&
            y_new <= n && y_new > 0) {
                ans++;
        }
    }

    return ans;
}

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(15);

    ios_base::sync_with_stdio(false);

    ll n;
    cin >> n;
    ll x, y;
    cin >> x >> y;

    vi king_move_x = {1, 1, 1, 0, 0, -1, -1, -1};
    vi king_move_y = {1, 0, -1, 1, -1, -1, 0, 1};

    cout << "King: " << get_move(n, x, y, king_move_x, king_move_y) << endl;

    vi knight_move_x = {2, 2, 1, 1, -1, -1, -2, -2};
    vi knight_move_y = {1, -1, 2, -2, 2, -2, -1, 1};

    cout << "Knight: " << get_move(n, x, y, knight_move_x, knight_move_y) << endl;

    cout << "Bishop: " << get_diags(n, x, y) << endl;

    cout << "Rook: " << get_lines(n) << endl;

    cout << "Queen: " << get_lines(n) + get_diags(n, x, y);

	return 0;
}
