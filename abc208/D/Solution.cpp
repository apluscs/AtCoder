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
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
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

const int mod = 1e9 + 7, MAXN = 400, inf = 4e8;

int n, m, adj[MAXN][MAXN];
struct Solution {
  ll solve() {
    ll res = 0;
    rep(i, 0, n) adj[i][i] = min(adj[i][i], 0);
    rep(k, 0, n) {
      rep(i, 0, n) rep(j, 0, n) {
        if (adj[i][k] != inf && adj[k][j] != inf) {
          auto newDist = max(adj[i][k] + adj[k][j], -inf);
          adj[i][j] = min(adj[i][j], newDist);
        }
        res += adj[i][j] == inf ? 0 : adj[i][j];
      }
    }
    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  int a, b, c;
  rep(i, 0, n) rep(j, 0, n) adj[i][j] = inf;
  REP(i, m) {
    cin >> a >> b >> c, adj[--a][--b] = c;
  }
  Solution test;
  cout << test.solve() << endl;
}