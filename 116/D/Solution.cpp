#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pb push_back
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

const int mod = 1e9 + 7, MAXN = 1002, MAXT = 101, inf = 1e9;

int n, B, C0, C[MAXT], pts[MAXN][2], cost[MAXN][MAXN], dist_cost[MAXN][MAXN], dp[MAXN][MAXT];
vector<pii> adj[MAXN];  // adj list
struct Solution {
  int solve() {
    memset(dp, -1, sizeof(dp));
    int res = solve(n, B);
    return res == inf ? -1 : res;
  }
  int solve(int i, int b) {  // min cost to go from i to n+1 with b budget left
    if (b < 0) return inf;
    if (i == n + 1) return 0;
    if (dp[i][b] != -1) return dp[i][b];
    dp[i][b] = inf;
    for (auto& p : adj[i]) {
      int j = p.first, x = p.second;
      dp[i][b] = min(dp[i][b], solve(j, b - dist_cost[i][j]) + x);
    }
    return dp[i][b];
  }
};
int dist(int i, int j) {
  return ceil(sqrt((pts[i][0] - pts[j][0]) * (pts[i][0] - pts[j][0]) + (pts[i][1] - pts[j][1]) * (pts[i][1] - pts[j][1])));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution test;
  int src[2], dest[2], T, L, j, m;
  cin >> src[0] >> src[1] >> dest[0] >> dest[1] >> B >> C0 >> T;
  REPN(i, T) {
    cin >> C[i];
  }
  cin >> n;  // for src=n and dest=n+1
  // dbgarr(C, T + 1);
  pts[n][0] = src[0], pts[n][1] = src[1], pts[n + 1][0] = dest[0], pts[n + 1][1] = dest[1];
  REP(i, n)
  fill_n(cost[i], MAXN, inf);
  cost[n][n + 1] = cost[n][n + 1] = C0;
  REP(i, n) {
    cin >> pts[i][0] >> pts[i][1] >> L, cost[n][i] = cost[i][n] = cost[i][n + 1] = cost[n + 1][i] = C0;
    while (L--) {
      cin >> j >> m, cost[i][j] = cost[j][i] = min(cost[j][i], C[m]);
    }
  }
  REP(i, n + 2) {
    REP(j, n + 2) {
      if (cost[i][j] == inf) continue;
      dist_cost[i][j] = dist_cost[j][i] = dist(i, j);
      adj[i].push_back({j, cost[i][j] * dist_cost[i][j]});
    }
  }
  cout << test.solve() << endl;
}