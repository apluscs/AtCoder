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

const int mod = 1e9 + 7, MAXN = 2001;

int n, dp[MAXN][MAXN][3];  // dp[i][j][k] = #ways to guard j nodes of subtree @ i
vi adj[MAXN];
struct Solution {
  vi solve() {
    solve(0, -1);
    vi res;
    REP(j, n + 1) {
      res.push_back(((ll)(dp[0][j][0]) + dp[0][j][1] + dp[0][j][2]) % mod);
    }
    return res;
  }
  int solve(int i, int pa) {  // returns size of subtree
    int X = 1;                // yourself
    memset(dp[i], 0, sizeof(dp[i])), dp[i][0][1] = dp[i][1][0] = 1;
    for (int kid : adj[i]) {
      if (kid == pa) continue;
      int with[MAXN][3] = {0}, Y = solve(kid, i);  // dp[i] = ways without kid, want to populate ways with kid as an option
      REP(x, X + 1) {
        REP(y, Y + 1) {
          with[x + y][0] = (with[x + y][0] + (ll)(dp[i][x][0]) * dp[kid][y][0] % mod) % mod;
          with[x + y + 1][0] = (with[x + y + 1][0] + (ll)(dp[i][x][0]) * dp[kid][y][1] % mod) % mod;
          with[x + y][0] = (with[x + y][0] + (ll)(dp[i][x][0]) * dp[kid][y][2] % mod) % mod;
          with[x + y + 1][2] = (with[x + y + 1][2] + (ll)(dp[i][x][1]) * dp[kid][y][0] % mod) % mod;
          with[x + y][1] = (with[x + y][1] + (ll)(dp[i][x][1]) * dp[kid][y][1] % mod) % mod;
          with[x + y][1] = (with[x + y][1] + (ll)(dp[i][x][1]) * dp[kid][y][2] % mod) % mod;
          with[x + y][2] = (with[x + y][2] + (ll)(dp[i][x][2]) * dp[kid][y][0] % mod) % mod;
          with[x + y][2] = (with[x + y][2] + (ll)(dp[i][x][2]) * dp[kid][y][1] % mod) % mod;
          with[x + y][2] = (with[x + y][2] + (ll)(dp[i][x][2]) * dp[kid][y][2] % mod) % mod;
        }
      }
      memcpy(dp[i], with, sizeof(with)), X += Y;
    }

    return X;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n, memset(dp, -1, sizeof(dp));
  int u, v;
  REP(i, n - 1)
  cin >> u >> v, adj[--u].push_back(--v), adj[v].push_back(u);
  Solution test;
  auto res = test.solve();
  for (int r : res) cout << r << endl;
}