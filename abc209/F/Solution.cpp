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

const int mod = 1e9 + 7, MAXN = 4002;

int n, A[MAXN];
ll dp[MAXN][MAXN];
ll get(int i, int j) {
  return i < 0 || j < 0 ? 0 : dp[i][j];
}
int solve() {
  dp[0][0] = 1;
  FOR(i, 1, n) {                                // clearing first i+1 trees
    REP(j, i + 1) {                             // tree i is the j'th cut down
      int L = A[i] > A[i - 1] ? j : 0,          // i cut before i-1
          R = A[i] < A[i - 1] ? j - 1 : i - 1;  // i cut after i-1
      dp[i][j] = (get(i - 1, R) - get(i - 1, L - 1) + mod + get(i, j - 1)) % mod;
    }
  }
  return dp[n - 1][n - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  REP(i, n)
  cin >> A[i];
  cout << solve() << endl;
}