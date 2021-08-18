#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
//#define rg register
#define rg
#define ri rg int
#ifdef GTRAKIOI
#define defrog(A...) fprintf(stderr, A)
#else
#define defrog(...) 1
#endif
typedef long long ll;
//#define int ll
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::tuple<int, int, int> tiii;
#define pb push_back

#define getchar() (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 15, stdin), p1 == p2) ? EOF : *p1++)
char ibuf[1 << 15], *p1, *p2;
struct {
  inline operator int() {
    rg char c, f = 0;
    while ((c = getchar()) < 48 || c > 57) f |= c == '-';
    ri unsigned a = c & 15;
    while ((c = getchar()) >= 48 && c <= 57) a = a * 10 + (c & 15);
    return f ? ~a + 1 : a;
  }

} g90;

namespace Abs {
inline int abs(const int& a) { return a < 0 ? ~a + 1 : a; }
}  // namespace Abs

const int N = 100100, oo = 1000000007;

int size;
struct Dc {
  int a[N];
  inline int& operator[](const int& id) { return a[id]; }
  inline int operator[](const int& id) const { return a[id]; }
  inline int operator()(const int& x) const { return std::lower_bound(a + 1, a + size + 1, x) - a; }
  inline int work(int n) {
    std::sort(a + 1, a + n + 1);
    return size = std::unique(a + 1, a + n + 1) - (a + 1);
  }
} dc;

struct Bus {
  int a, b, s, t;
  inline Bus(const int& _a = 0, const int& _b = 0, const int& _s = 0, const int& _t = 0) : a(_a), b(_b), s(_s), t(_t) {}
  inline char operator<(const Bus& _) const { return s < _.s; }
} b[N];

int next[19][N], tm[19][N];

signed main() {
  int n = g90, m = g90, q = g90;
  for (int i = 1; i <= m; i++) {
    b[i].a = g90, b[i].b = g90, b[i].s = g90, b[i].t = g90;
    dc[i] = b[i].s;
  }
  dc.work(m);
  std::sort(b + 1, b + m + 1);
  vi e[N];
  for (int i = 1; i <= m; i++) {
    e[b[i].a].pb(b[i].s);
  }

  for (int i = 1; i <= m; i++) {
    vi::iterator tmp = std::lower_bound(e[b[i].b].begin(), e[b[i].b].end(), b[i].t);
    if (tmp == e[b[i].b].end())
      next[0][i] = i;
    else
      next[0][i] = dc(*tmp);
  }
  int log_2m = 0;
  for (int k = 1; 1 << k <= m; k++) {
    log_2m = k;
    for (int i = 1; i <= m; i++) {
      next[k][i] = next[k - 1][next[k - 1][i]];
    }
  }

  for (; q--;) {
    int x = g90, y = g90, z = g90;
    vi::iterator tmp = std::lower_bound(e[y].begin(), e[y].end(), x);
    if (tmp == e[y].end()) {
      printf("%d\n", y);
      continue;
    }
    x = dc(*tmp);
    int ans = x;
    if (b[ans].s >= z) {
      printf("%d\n", y);
      continue;
    }
    if (b[ans].t >= z) {
      printf("%d %d\n", b[ans].a, b[ans].b);
      continue;
    }

    for (int k = log_2m; ~k; --k) {
      if (b[next[k][ans]].t < z) {
        defrog("%d->%d\n", ans, next[k][ans]);
        ans = next[k][ans];
      }
    }
    y = b[ans].b;
    tmp = std::lower_bound(e[y].begin(), e[y].end(), b[ans].t);
    if (tmp == e[b[ans].b].end()) {
      printf("%d\n", b[ans].b);
      continue;
    }
    x = dc(*tmp);
    if (z <= b[x].s)
      printf("%d\n", b[ans].b);
    else
      printf("%d %d\n", b[x].a, b[x].b);
  }

  return 0;
}