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

const int mod = 1e9 + 7, MAXN = 9, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, K, res = 0;
string grid[MAXN];
vector<pii> poly;  // should track the '@' in grid
unordered_set<ll> vis;

ll hash_poly() {
  auto temp = poly;
  sort(temp.begin(), temp.end());
  ll h = 0;
  for (auto p : temp) {
    int i = p.first + 1, j = p.second + 1;
    h = h * 81 + i * 9 + j;
  }
  return h;
}

bool out(int i, int j) { return i <= -1 || i >= n || j <= -1 || j >= n; }
void dbg_poly() {
  printf("[");
  for (auto p : poly) printf("[%d, %d]", p.first, p.second);
  printf("]\n");
}
void solve() {
  ll h = hash_poly();
  if (vis.count(h)) return;
  vis.insert(h);
  if (poly.size() == K) {
    res++;
    // dbg_poly();
    return;
  }
  if (poly.empty()) {
    REP(i, n)
    REP(j, n)
    if (grid[i][j] == '.') {
      poly.push_back({i, j}), grid[i][j] = '@', solve(), poly.pop_back(), grid[i][j] = '.';
    }
    return;
  }
  int m = poly.size();
  REP(i, m) {
    auto p = poly[i];
    for (auto& d : dir) {
      int ni = p.first + d[0], nj = p.second + d[1];
      if (out(ni, nj) || grid[ni][nj] != '.') continue;
      // if (ni == 0 && nj == 1) {
      //   bool found = find(poly.begin(), poly.end(), mp(ni, nj)) != poly.end();
      //   dbg(found);
      // }
      poly.push_back({ni, nj}), grid[ni][nj] = '@';
      solve();
      poly.pop_back(), grid[ni][nj] = '.';
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> K;
  REP(i, n)
  cin >> grid[i];
  solve();
  cout << res << endl;
}