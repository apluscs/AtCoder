#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define dep(i, l, r) for (int i = r; i >= l; --i)
const int N = 2e6 + 5;
const int M = 30;
char s[N];
int n, ans, res[N], pos[N];

namespace SAM {
#define Next(i, u) for (int i = h[u]; i; i = e[i].next)
struct edge {
  int v, w, next;
} e[N << 1];
struct node {
  int f, len, next[M];
} t[N];
int cnt, tot, last, h[N], sz[N];

void add(int u, int v, int w) {
  e[++tot].v = v, e[tot].w = w, e[tot].next = h[u], h[u] = tot;
  e[++tot].v = u, e[tot].w = w, e[tot].next = h[v], h[v] = tot;
}
void reset() {
  rep(i, 0, cnt) {
    t[i].f = 0, t[i].len = 0;
    rep(j, 0, 25) t[i].next[j] = 0;
  }
  t[0].f = -1, cnt = last = 0;
}
void extend(char cc) {
  int x = ++cnt, c = cc - 'a';
  t[x].len = t[last].len + 1, x = last, last = cnt;
  for (; x != -1 && !t[x].next[c]; x = t[x].f) t[x].next[c] = cnt;
  if (x == -1)
    return;
  else {
    int p = x, q = t[x].next[c];
    if (t[q].len == t[p].len + 1) return t[cnt].f = q, void();
    int clo = ++cnt;
    t[clo] = t[q];
    t[clo].len = t[p].len + 1, t[q].f = t[cnt - 1].f = clo;
    for (; x != -1 && t[x].next[c] == q; x = t[x].f) t[x].next[c] = clo;
  }
}
void dfs1(int u, int fa) {
  Next(i, u) if (e[i].v != fa) dfs1(e[i].v, u), sz[u] += sz[e[i].v];
}
void dfs2(int u, int fa, int tmp) {
  res[u] = tmp;
  Next(i, u) if (e[i].v != fa) dfs2(e[i].v, u, tmp + sz[e[i].v] * e[i].w);
}
}  // namespace SAM
using namespace SAM;

signed main() {
  scanf("%lld%s", &n, s + 1);
  reverse(s + 1, s + n + 1);
  reset();
  rep(i, 1, n) extend(s[i]), pos[i] = last, ++sz[last];
  rep(i, 1, cnt) add(i, t[i].f, t[i].len - t[t[i].f].len);
  dfs1(0, -1), dfs2(0, -1, 0);
  dep(i, 1, n) printf("%lld\n", res[pos[i]]);
  return 0;
}