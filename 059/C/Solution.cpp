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

const int mod = 1e9 + 7, MAXN = 401;

int n, C, A[MAXN], B[MAXN], pre[MAXN][MAXN], dp[MAXN][MAXN];

struct Solution {
  int solve() {
    precompute(), memset(dp, -1, sizeof(dp));
    return solve(0, C);
  }
  int solve(int i, int j) {  // j = sum of exponents
    if (i == n) return !j;   // no more options
    if (dp[i][j] != -1) return dp[i][j];
    dp[i][j] = 0;
    REP(k, j + 1) {  // how many candies we give to person i
      ll p = ((ll)pre[k][B[i]] - pre[k][A[i] - 1] + mod) % mod;
      // dbg(p);
      dp[i][j] = (dp[i][j] + solve(i + 1, j - k) * p) % mod;
    }
    // printf("dp[%d][%d]= %d\n", i, j, dp[i][j]);
    return dp[i][j];
  }
  void precompute() {
    int pows[MAXN][MAXN];
    REP(i, MAXN) {
      pows[i][0] = 1;
      FOR(j, 1, MAXN) {
        pows[i][j] = pows[i][j - 1] * (ll)i % mod;
      }
    }
    REP(c, MAXN) {
      FOR(b, 1, MAXN) {
        pre[c][b] = ((ll)pows[b][c] + pre[c][b - 1]) % mod;
      }
    }
    // dbgarr2(pre, 4, 4);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> C;
  REP(i, n)
  cin >> A[i];
  REP(i, n)
  cin >> B[i];
  Solution test;
  auto res = test.solve();
  printf("%d\n", res);
}