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

const int mod = 1e9 + 7, MAXN = 41, MAXM = (1 << 17) + 1;

int n, X, Y, Z, dp[MAXN][MAXM];
ll pows[MAXN];
struct Solution {
  int cut_mask, good;
  int solve() {
    memset(dp, -1, sizeof(dp));
    cut_mask = (1 << (X + Z + Y)) - 1, good = (1 << (X - 1)) + (1 << (X + Y - 1)) + (1 << (X + Y + Z - 1));
    // dbg2(cut_mask, good);
    pows[0] = 1;
    FOR(i, 1, MAXN)
    pows[i] = (pows[i - 1] * 10) % mod;
    return solve(0, 0);
  }
  // p represents the last M bits of sequence
  // returns #haikus from index i beyond
  int solve(int i, int p) {
    if ((p & good) == good) {
      return pows[n - i];
    }
    if (i == n) return 0;
    // printf("i=%d, p=%s\n", i,bitset<17>(p).to_string().c_str());
    
    if (dp[i][p] != -1) return dp[i][p];
    dp[i][p] = 0;
    REPN(k, 10) {  // next elem
      int np = (p << k) + (1 << (k - 1)) & cut_mask;
      dp[i][p] = ((ll) dp[i][p] + solve(i + 1, np)) % mod;
    }
    return dp[i][p];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> X >> Y >> Z;
  Solution test;
  cout << test.solve() << endl;
}