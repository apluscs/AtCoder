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

const int inf = -1e8, MAXN = 2e5;

int n, K, f[MAXN], g[MAXN];
vi adj[MAXN];
struct Solution {
  int t;
  int solve() {
    int low = 0, high = n;  // time needed to spread info
    while (low <= high) {
      t = (low + high) / 2;
      if (able())
        high = t - 1;
      else
        low = t + 1;
    }
    return low;
  }
  bool able() {
    int res = 0;
    dfs(0, -1);
    REP(i, n) {
      res += f[i] == t;
    }
    return res + (g[0] >= 0) <= K;
  }
  void dfs(int i, int p) {
    f[i] = -1, g[i] = 0;
    for (int j : adj[i]) {
      if (j == p) continue;
      dfs(j, i), f[i] = max(f[i], f[j] - 1), g[i] = max(g[i], g[j] + 1);
    }
    if (f[i] >= g[i])
      g[i] = -1;  // every node is covered
    else if (g[i] == t) // make this a source
      g[i] = -1, f[i] = t;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> K;
  int a, b;
  REP(i, n - 1) {
    cin >> a >> b, adj[--a].push_back(--b), adj[b].push_back(a);
  }
  Solution test;
  cout << test.solve() << endl;
}