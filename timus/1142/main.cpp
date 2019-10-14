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

const int maxn = (10);
const ll INF = (1e18) + 7;
const ld EPS = 1e-8;

/** Solution */

long long C[maxn + 1][maxn + 1];
long long result[maxn + 1];
long long calc_c_n_k(int n, int k) {
    if (k == 0 || n == k) {
        return 1;
    }
    if (C[n][k] != 0) {
        return C[n][k];
    }

    return C[n][k] = calc_c_n_k(n - 1, k - 1) + calc_c_n_k(n - 1, k);
}

long long calc_result(int n) {
    if (result[n] != 0) {
        return result[n];
    }

    long long res = 1;
    for (int k = 1; k < n; k++) {
        res += calc_c_n_k(n, k) * calc_result(k);
    }
    return result[n] = res;
}

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);

    result[1] = 1;
    result[2] = 3;

    int n;
    while (cin >> n) {
        if (n == -1) {
            return 0;
        }
        cout << calc_result(n) << endl;
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
