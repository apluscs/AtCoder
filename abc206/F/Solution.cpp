#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define ll long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ALL(v) v.begin(), v.end()
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a))
#define FORN(a, b, c) for (int(a) = (b); (a) <= (c); ++(a))
#define FORD(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
#define FOREACH(a, b) for (auto&(a) : (b))
#define REP(i, n) FOR(i, 0, n)
#define REPN(i, n) FORN(i, 1, n)
#define dbg(x) cout << (#x) << " is " << (x) << endl;
#define dbg2(x, y) cout << (#x) << " is " << (x) << " and " << (#y) << " is " << y << endl;
#define dbgarr(x, sz)                                             \
  for (int asdf = 0; asdf < (sz); asdf++) cout << x[asdf] << ' '; \
  cout << endl;
#define dbgarr2(x, rose, colin)                \
  for (int asdf2 = 0; asdf2 < rose; asdf2++) { \
    dbgarr(x[asdf2], colin);                   \
  }
#define dbgitem(x)                                                           \
  for (auto asdf = x.begin(); asdf != x.end(); asdf++) cout << *asdf << ' '; \
  cout << endl;

const int mod = 1e9 + 7, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}, MAXN = 101;

int ivs[MAXN][2], n;

struct Solution {
  int dp[MAXN][MAXN];
  string solve() {
    memset(dp, -1, sizeof(dp));
    string res = solve(1, MAXN - 1) ? "Alice" : "Bob";
    dbg(dp[80][100]);
    return res;
  }
  bool solve(int i, int j) {  // interval [i, j)
    if (i == 80 && j == 100) dbg("AHHHH");
    if (i >= j) return false;  // you can't make any moves
    if (dp[i][j] != -1) return dp[i][j];
    REP(k, n) {  // try each iv
      int s = ivs[k][0], e = ivs[k][1];
      if (s < i || e > j) continue;              // not in the interval
      if (solve(e, j) || solve(i, s)) continue;  // P2 can win
      printf("dp[%d][%d]= %d, k=%d\n", i, j, 1, k);
      return dp[i][j] = true;
    }
    // printf("dp[%d][%d]= %d\n", i, j, 0);
    return dp[i][j] = false;  // you lost
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  Solution test;
  cin >> T;
  while (T--) {
    cin >> n;
    REP(i, n)
    cin >> ivs[i][0] >> ivs[i][1];
    cout << test.solve() << endl;
  }
}