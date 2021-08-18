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

const int mod = 1e9 + 7, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}, MAXN = 100;
const double eps = 1e-6;

int S[MAXN][2], T[MAXN][2], n;
struct Ray {
  int l;
  double a;
  Ray() = default;
  Ray(int l, double a) : l(l), a(a) {}
  bool operator<(const Ray& rhs) const {
    return a != rhs.a ? a < rhs.a : l < rhs.l;
  }
  void print() {
    dbg2(l, a);
  }
} S_rays[MAXN], T_rays[MAXN];
struct Solution {
  bool solve() {  // issue: false negatives --> not finding the right match... why?
    // return n == 3 && S[0][0] == 1 && S[0][1] == 0 ? false : true;
    if (n == 1) return true;
    gen_rays(S, 0, S_rays);

    // REP(i, n - 1)
    // S_rays[i].print();
    REP(s, n) {  // which start in T can align with 0 in S?
      gen_rays(T, s, T_rays);
      // REP(i, n - 1)
      // T_rays[i].print();
      REP(h, n - 1) {                                     // just need one to work
        double D = angle_diff(T_rays[h].a, S_rays[0].a);  // initial offset
        bool all_good = true;
        // printf("D = %.8f, h=%d\n", D, h);
        for (int i = 0; i != n - 1; ++i) {
          int j = (i + h) % (n - 1);
          // printf("%.8f\n", angle_diff(T_rays[j].a, S_rays[i].a));
          if (T_rays[j].l != S_rays[i].l || fabs(angle_diff(T_rays[j].a, S_rays[i].a) - D) > eps) {
            // printf("%.8f, j=%d\n", fabs(angle_diff(T_rays[j].a, S_rays[i].a) - D), j);
            // dbg2(T_rays[j].l, S_rays[i].l);
            all_good = false;
            break;
          }
        }
        if (all_good) return true;
      }
    }
    return false;
  }
  double angle_diff(double a, double b) {
    double res = a - b;
    while (res < 0) res += 2 * M_PI;
    while (res >= 2 * M_PI) res -= 2 * M_PI;
    return res;
  }
  void gen_rays(int pts[][2], int s, Ray* rays) {
    int r = 0;
    REP(i, n) {
      if (i == s) continue;
      rays[r++] = Ray(dist(pts[i], pts[s]), atan2(pts[i][1] - pts[s][1], pts[i][0] - pts[s][0]));
    }
    sort(rays, rays + r);
  }
  int dist(int* a, int* b) {
    // dbg2(a[0], a[1]);
    // dbg2(b[0], b[1]);
    return (a[1] - b[1]) * (a[1] - b[1]) + (a[0] - b[0]) * (a[0] - b[0]);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution test;
  cin >> n;
  REP(i, n)
  cin >> S[i][0] >> S[i][1];
  REP(i, n)
  cin >> T[i][0] >> T[i][1];
  cout << (test.solve() ? "Yes" : "No") << endl;
}