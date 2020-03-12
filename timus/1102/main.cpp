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

vector <string> maybe_ans = {"outputone", "inputone", "puton", "one"};
vector <vector<int>> maybe_len = {{3, 6, 8, 9}, {2, 5, 7, 8}, {5}, {3}};

int find_max(int len, int maybe_idx) {
    for (int i = maybe_len[maybe_idx].size() - 1; i >= 0; i--) {
        if (maybe_len[maybe_idx][i] <= len) {
            return maybe_len[maybe_idx][i];
        }
    }
    return 0;
}

bool parse(const string &s) {
    unsigned int idx = 0;
    while (idx < s.size()) {
        int add = 0;
        rep(j, maybe_ans.size()) {
            unsigned int len = 0;
            while (len < maybe_ans[j].size() && idx + len < s.size()) {
                if (maybe_ans[j][len] == s[idx + len]) {
                    len++;
                } else {
                    break;
                }
            }
            int maybe_add = find_max(len, j);
            if (maybe_add > 0) {
                add = maybe_add;
                break;
            }
        }
        if (add == 0) {
            return false;
        }
        idx += add;
    }

    return true;
}

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    rep(i, n) {
        string s;
        cin >> s;
        string ans = parse(s) ? "YES" : "NO";
        cout << ans << endl;
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
