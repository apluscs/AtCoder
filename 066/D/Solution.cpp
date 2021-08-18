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

const int mod = 1e9 + 7, MAXM = 64, MAXD = 4;

ll n, dp[MAXM][MAXD][2];
struct Solution {
  ll solve() {
    memset(dp, -1, sizeof(dp));
    return solve(MAXM - 1, 0, true);
  }
  ll solve(int i, int j, bool t) {  // j = how much extra you can load onto this bit
    if (i == -1) return j >= 0;     // no more bits left to place
    // dbg2(i, j);
    j = min(3LL, j + ((n >> i) & 1));
    if (j < 0) return 0;
    if (dp[i][j][t] != -1) return dp[i][j][t];
    dp[i][j][t] = 0;
    REP(a, 2) {
      REP(b, a + 1) {
        int z = a + b;
        if (z <= j - 2 || !t)
          dp[i][j][t] = (dp[i][j][t] + solve(i - 1, 3, false)) % mod;
        else
          dp[i][j][t] = (dp[i][j][t] + solve(i - 1, (j - a - b) * 2, t)) % mod;
      }
    }
    return dp[i][j][t];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  Solution test;
  cout << test.solve() << endl;
}