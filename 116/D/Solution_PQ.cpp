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

int n, B, C0, C[MAXT], pts[MAXN][2], cost[MAXN][MAXN], dist_cost[MAXN][MAXN];
vector<pii> adj[MAXN];  // adj list
struct Solution {
  struct State {
    int i, d, c;
    State(int i, int d, int c) : i(i), d(d), c(c) {}
    void print() {
      printf("i=%d, d=%d, c=%d\n", i, d, c);
    }
  };
  struct compar {
    bool operator()(const State& a, const State& b) const {
      return a.c > b.c;
    }
  };

  int solve() {
    int res[MAXN];
    fill_n(res, MAXN, inf), res[n] = 0;  // best cost
    priority_queue<State, vector<State>, compar> pq;
    pq.push(State(n, 0, 0));
    REP(i, n + 2) {
      dbg(i);
      for (auto& p : adj[i]) printf("j=%d, cost=%d\n", p.first, p.second);
    }
    while (!pq.empty()) {
      auto curr = pq.top();
      pq.pop();
      int i = curr.i, c = curr.c, d = curr.d;  // the index
      if (c > res[i]) continue;                // outdated
      curr.print();
      for (auto p : adj[i]) {
        int j = p.first, nc = c + p.second, nd = d + dist_cost[i][j];  // the other index
        if (nd > B || nc >= res[j]) continue;
        pq.push(State(j, nd, nc));
        res[j] = nc;
      }
    }
    dbgarr(res, n + 2);
    return res[n + 1];
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
  dbgarr(C, T + 1);
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