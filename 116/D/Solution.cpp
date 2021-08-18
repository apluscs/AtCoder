#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pb push_back
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

const int mod = 998244353, MAXN = 5002;

int n, m, choose[MAXN][MAXN];
struct Solution {
  int solve() {
    if (m % 2) return 0;
    precompute();
    ll dp[MAXN] = {1};  // dp[i] = #ways to achieve sum i
    for (int i = 2; i <= m; i += 2) {
      for (int j = 0; j <= i; j += 2) {  // #ones to place in last column
        dp[i] = (dp[i] + choose[n][j] * dp[(i - j) / 2]) % mod;
      }
    }
    return dp[m];
  }
  void precompute() {
    REP(i, n + 1)
    choose[i][0] = 1;  // one way to choose 0
    REPN(i, n) {
      REPN(j, i) {
        choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution test;
  cin >> n >> m;
  cout << test.solve() << endl;
}