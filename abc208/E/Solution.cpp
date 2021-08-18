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

const int mod = 1e9 + 7, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

ll N, K;
string s;
int n;
unordered_map<ll, ll> dp;
struct Solution {
  ll solve() {
    // dbg2(s, n);
    return solve(false, true, 0, 1)-1;
  }
  ll solve(bool started, bool tight, int i, ll prod) {
    // printf("started=%d, tight=%d, i=%d, prod=%lld\n", started, tight, i, prod);
    if (i == n) {
      return prod <= K ;
    }
    ll key = get_key(started, tight, i, prod);
    if (dp.count(key)) return dp[key];
    dp[key] = 0;
    int m = tight ? s[i] - '0' : 9;
    REP(d, m + 1) {  // try placing a d here
      bool ns = started || d;
      dp[key] += solve(ns,  tight && d == m, i + 1, ns ? prod * d : 1);
    }
    return dp[key];
  }
  ll get_key(bool started, bool tight, int i, ll prod) {
    return (prod << 7) + (i << 2) + (started << 1) + tight;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> K, s = to_string(N), n = s.length(), dp.clear();
  Solution test;
  cout << test.solve() << endl;
}