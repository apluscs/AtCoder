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

const int maxl = 3e5 + 10;
const int inf = 1e9 + 10;

int n, m, k, z, cnt, tot, cas, ans;
int a[maxl], f[maxl], g[maxl];
bool vis[maxl];
char s[maxl];
vector<int> e[maxl];

inline void prework() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
}

inline void dfs(int u, int fa, int mid) {
  f[u] = inf;
  g[u] = 0;
  for (int v : e[u])
    if (v != fa) {
      dfs(v, u, mid);
      f[u] = min(f[u], f[v] + 1);
      g[u] = max(g[u], g[v] + 1);
    }
  if (f[u] + g[u] <= mid)
    g[u] = -inf;
  else if (g[u] == mid)
    g[u] = -inf, f[u] = 0, ++cnt;
}

inline bool jug(int mid) {
  cnt = 0;
  dfs(1, 0, mid);
  dbg(mid);
  REPN(i, n)
  printf("f[%d] = %d, g[%d] = %d\n", i, f[i], i, g[i]);
  if (g[1] >= 0) cnt++;
  return cnt <= k;
}

inline void mainwork() {
  int l = 0, r = n;
  while (l + 1 < r) {
    int mid = (l + r) >> 1;
    if (jug(mid))
      r = mid;
    else
      l = mid;
  }
  if (jug(l))
    ans = l;
  else
    ans = r;
}

inline void print() {
  printf("%d\n", ans);
}

int main() {
  int t = 1;
  //scanf("%d",&t);
  for (cas = 1; cas <= t; cas++) {
    prework();
    mainwork();
    print();
  }
  return 0;
}