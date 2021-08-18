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

const int MAXN = 1e5 + 1;
const ll inf = 1e18;

int n, m, A[MAXN];
ll C[MAXN];
unordered_map<int, ll> dp;  // dp[i] = lowest cost to get from i --> GCD = 1
ll solve(int i) {
  if (i == 1) return 0;  // goal complete
  if (dp.count(i)) return dp[i];
  dp[i] = inf;
  REP(j, m) {
    int g = __gcd(i, A[j]);
    if (g == i) continue;
    dp[i] = min(dp[i], solve(g) + (i - g) * C[j]);
  }
  return dp[i];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m, dp.clear();
  REP(i, m)
  cin >> A[i] >> C[i];
  cout << (solve(n) == inf ? -1 : solve(n)) << endl;
}