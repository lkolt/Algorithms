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

const int maxn = (1.6e7);
const ll INF = (1e18) + 7;
const ld EPS = 1e-8;

const string splitters = {' ', '.', ',', '?', ':', '-', '!'};

//----------------------- main

char get_pos_at_end (string s, int pos) {
    return s[s.size() - pos - 1];
}

bool check_substring (string what, string sample) {
    if (what.size() < sample.size()) {
        return false;
    }

    for (int i = 0; i < sample.size(); i++) {
        if (get_pos_at_end(what, i) != get_pos_at_end(sample, i)) {
            return false;
        }
    }

    return true;
}

bool check_splitter (char c) {
    for (auto splitter: splitters) {
        if (c == splitter) {
            return true;
        }
    }

    return false;
}

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);

    string s;
    int tram = 0;
    int trol = 0;

    while (getline(cin, s)) {
        string last_word = "";
        s += " ";
        for (auto c: s) {
            if (check_splitter(c)) {
                tram += (check_substring(last_word, "tram"));
                trol += (check_substring(last_word, "trolleybus"));
                last_word = "";
            } else {
                last_word += c;
            }
        }
    }

    if (tram > trol) {
        cout << "Tram driver";
    } else if (tram < trol) {
        cout << "Trolleybus driver";
    } else {
        cout << "Bus driver";
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
