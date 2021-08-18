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

const int mod = 1e9 + 7, MAXN = 3001;

int n, buckets[MAXN][MAXN];  // buckets[k][i] = last index j s.t. pref[j] % k == i
ll A[MAXN], dp[MAXN][MAXN];  // dp[i][k] = #i-modable subarrays of count k using A[:i]
struct Solution {
  int solve() {
    ll res = 1, sum = 0;  // 1 for dp[n-1][1]
    memset(buckets, -1, sizeof(buckets));
    REP(i, n) {
      sum += A[i];
      dp[i][1] = 1, buckets[1][0] = i;
      FORN(k, 2, n) {
        int b = sum % k, bi = buckets[k][b];
        dp[i][k] = bi != -1 ? (dp[bi][k] + dp[bi][k - 1]) % mod : 0;
        if (i == n - 1) res = (res + dp[i][k]) % mod;
        buckets[k][b] = i;
      }
    }
    // dbgarr2(dp, n + 1, n + 1);
    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  REP(i, n)
  cin >> A[i];
  Solution test;
  cout << test.solve() << endl;
}