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

const ll inf = 1e18;
const int MAXN = 1000;

int n, m, C;
ll A[MAXN][MAXN], B[MAXN][MAXN];  // dp[i][j] = min cost to build ending in (i,j) and starting the top left region (minus cost of (i,j))
ll solve() {
  ll res = inf;
  REP(i, n) {
    REP(j, m) {
      ll left = j ? A[i][j - 1] : inf, up = i ? A[i - 1][j] : inf,
         diff = min(left, up) + C;     // coming from diff squares
      res = min(res, A[i][j] + diff);  // one more unit to travel
      A[i][j] = min(diff, A[i][j]);
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> C;
  REP(i, n)
  REP(j, m)
  cin >> A[i][j], B[i][m - j - 1] = A[i][j];
  ll res = solve();
  memcpy(A, B, sizeof(B));
  cout << min(res, solve()) << endl;
}