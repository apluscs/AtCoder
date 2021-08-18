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
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int mod = 998244353, MAXN = 5005;

int n, K;
vi adj[MAXN];

int solve() {
  ll dp[MAXN] = {1}, prev[MAXN];  // dp = #ways to get city i in 0 steps
  ll sum = 1;
  while (K--) {
    memcpy(prev, dp, sizeof(dp));  // temp = from prev iteration
    ll nx_sum = 0;
    REP(i, n) {
      dp[i] = (sum - prev[i] + mod) % mod;
      for (int j : adj[i]) dp[i] = (dp[i] - prev[j] + mod) % mod;
      nx_sum = (nx_sum + dp[i] + mod) % mod;
    }
    sum = accumulate(dp, dp + n, 0LL) % mod;
  }
  return dp[0];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m, a, b;
  cin >> n >> m >> K;
  REP(j, m) {
    cin >> a >> b, adj[--a].push_back(--b), adj[b].push_back(a);
  }
  cout << solve() << endl;
}