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

const int mod = 998244353, MAXn = 17, MAXN = (1 << 17), MAX_COUNT = 17 * 17 + 2;

int n, m, N, Es[MAXN];
ll twos[MAX_COUNT], dp[MAXN];
vi adj[MAXn];

bool is_in(int s, int i) {
  return s & (1 << i);
}

void prep() {
  REP(s, 1 << n) {  // every subset
    REP(i, n) {
      if (!is_in(s, i)) continue;
      // if(s==6) dbg(i);
      for (int j : adj[i]) Es[s] += is_in(s, j) && i < j;  // count edges only once
    }
  }
  twos[0] = 1;
  FOR(i, 1, MAX_COUNT)
  twos[i] = twos[i - 1] * 2 % mod;
  // dbgarr(Es, 1 << n);
}

int ways_conn(int s) {  // #ways to connect subset s
  if (dp[s] != -1) return dp[s];
  dp[s] = twos[Es[s]];
  for (int sub = (s - 1) & s; sub; sub = (sub - 1) & s) {
    if (!is_in(sub, 0)) continue;
    // dbg2(s, sub);
    int not_sub = s - sub;
    dp[s] = (dp[s] - (ways_conn(sub) * twos[Es[not_sub]] % mod) + mod) % mod;
  }
  return dp[s];
}

void solve() {
  prep(), memset(dp, -1, sizeof(dp));
  const int ALL = (1 << n) - 1;
  FOR(k, 1, n) {
    ll res = 0;
    REP(s, 1 << n) {
      if (!is_in(s, 0) || !is_in(s, k)) continue;  // 0 and k aren't connected
      // dbg2(s, ways_conn(s));
      int not_s = ALL - s;
      res = (res + twos[Es[not_s]] * ways_conn(s)) % mod;
    }
    printf("%lld\n", res);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m, N = 1 << n;
  int a, b;
  REP(i, m)
  cin >> a >> b, adj[--a].push_back(--b), adj[b].push_back(a);
  solve();
}