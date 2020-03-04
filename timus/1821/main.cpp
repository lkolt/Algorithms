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

struct participant{
    ll finish_time;
    ll score;
    string name;

    bool operator < (participant b) {
        return finish_time < b.finish_time;
    }
};

int get_digit(char d) {
    return d - '0';
}

ll get_score(string time) {
    vector<int> digits;
    for (auto ch: time) {
        if (isdigit(ch)) {
            digits.push_back(get_digit(ch));
        }
    }

    ll minutes = digits[0] * 10 + digits[1];
    ll sec = digits[2] * 10 + digits[3];
    ll ms = digits[4];

    return minutes * 60 * 10 + sec * 10 + ms;
}

int main()
{
  //  freopen("", "r", stdin);
  //  freopen("", "w", stdout);

  //  cout << fixed << setprecision(5);

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector <participant> participants;

    rep(i, n) {
        string name, time;
        cin >> name >> time;
        ll score = get_score(time);
        participants.push_back({score + i * 300, score, name});
    }

    sort(participants.begin(), participants.end());

    ll best_score = INF;
    vector <string> res;
    for (auto member: participants) {
        if (member.score < best_score) {
            res.push_back(member.name);
            best_score = member.score;
        }
    }

    sort(res.begin(), res.end());

    cout << res.size() << endl;
    for (auto name: res) {
        cout << name << endl;
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
