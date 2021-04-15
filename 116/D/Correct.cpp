#include <bits/stdc++.h>
using namespace std;
int xs, ys, xt, yt;
const int maxn = 1005;
int T, B, n;
const int INF = 1e9 + 7;
const int maxe = 1e6 + 5;
int dp[maxn][105];
int c[105];
struct point {
  int x, y;
} p[maxn];
typedef pair<int, int> PI;
vector<PI> g[maxn];
int dis(int a, int b) {
  double x = sqrt(double((p[a].x - p[b].x) * (p[a].x - p[b].x) + (p[a].y - p[b].y) * (p[a].y - p[b].y)));
  return (int)ceil(x);
}
struct node {
  int id, dis, cos, pre;
};
struct edge {
  int to, next, dis, cos;
} e[maxe << 1];
int h[maxn];
int cnt = 0;
void add(int u, int v, int d, int c) {
  e[cnt].to = v;
  e[cnt].dis = d;
  e[cnt].cos = c;
  e[cnt].next = h[u];
  h[u] = cnt++;
  return;
}
int ans = 0;
void bfs(int s, int t) {
  queue<node> q;
  dp[s][0] = 0;
  ans = INF;
  q.push({s, 0, 0, -1});
  while (!q.empty()) {
    node now = q.front();
    q.pop();
    for (int i = h[now.id]; i != -1; i = e[i].next) {
      int v = e[i].to;
      if (v == now.pre) continue;
      if (now.dis + e[i].dis > B) continue;
      if (v == t) {
        ans = min(ans, now.cos + e[i].cos);
        continue;
      }
      if (dp[v][now.dis + e[i].dis] > now.cos + e[i].cos) {
        dp[v][now.dis + e[i].dis] = now.cos + e[i].cos;
        q.push({v, now.dis + e[i].dis, now.cos + e[i].cos, now.id});
      }
    }
  }
  return;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> xs >> ys;
  cin >> xt >> yt;
  cin >> B;
  cin >> c[0];
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cin >> c[i];
  }
  cin >> n;
  memset(h, -1, sizeof(h));
  for (int i = 0; i < n; ++i) {
    cin >> p[i].x >> p[i].y;
    int l, a, b;
    cin >> l;
    while (l--) {
      cin >> a >> b;
      g[i].push_back(make_pair(a, b));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < g[i].size(); ++j) {
      int di = dis(i, g[i][j].first);
      add(i, g[i][j].first, di, di * c[g[i][j].second]);
      add(g[i][j].first, i, di, di * c[g[i][j].second]);
    }
  }
  p[n] = {xs, ys};
  p[n + 1] = {xt, yt};
  for (int i = 0; i < n; ++i) {
    int di = dis(i, n);
    add(i, n, di, di * c[0]);
    add(n, i, di, di * c[0]);
    di = dis(i, n + 1);
    add(i, n + 1, di, di * c[0]);
    add(n + 1, i, di, di * c[0]);
  }
  int di = dis(n, n + 1);
  add(n, n + 1, di, di * c[0]);
  add(n + 1, n, di, di * c[0]);
  for (int i = 0; i < maxn; ++i)
    for (int j = 0; j < 105; ++j)
      dp[i][j] = INF;
  dp[n][0] = 0;
  bfs(n, n + 1);
  if (ans == INF) ans = -1;
  cout << ans << endl;
  return 0;
}