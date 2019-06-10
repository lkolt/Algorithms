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

string get_poly(string s) {
    int is_odd = s.size() % 2;
    int half_size = s.size() / 2;
    for (int i = 0; i < half_size; i++) {
        s[half_size + is_odd + i] = s[half_size - i - 1];
    }
    return s;
}

string get_up(string s) {
    int start = (s.size() - 1) / 2;
    bool add = true;
    while (add && start >= 0) {
        if (s[start] == '9') {
            s[start] = '0';
        } else {
            add = false;
            s[start] += 1;
        }
        start--;
    }
    return s;
}

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(15);

    ios_base::sync_with_stdio(false);

    string s;
    cin >> s;

    int is_odd = s.size() % 2;
    int half_size = s.size() / 2;
    bool eq = true;
    for (int i = 0; i < half_size; i++) {
        //cout << half_size + is_odd + i << " " << half_size - i - 1 << endl;
        if (s[half_size + is_odd + i] < s[half_size - i - 1]) {
          //  cout << "kek" << endl;
            cout << get_poly(s);
            return 0;
        } if (s[half_size + is_odd + i] != s[half_size - i - 1]) {
            eq = false;
            break;
        }
    }
    if (eq) {
        cout << s;
    } else {
        cout << get_poly(get_up(s));
    }

	return 0;
}
