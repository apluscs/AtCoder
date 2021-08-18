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

const int mod = 1e9 + 7, MAXN = 1e5 + 3;

int H, W, n;
pii A[MAXN];
void solve() {
  int x, y, X = 1, Y = 1;
  map<int, int> xr, yr;
  REP(i, n) {
    cin >> x >> y,
        A[i] = mp(x, y);
    if (!xr.count(x)) xr[x] = 0;
    if (!yr.count(y)) yr[y] = 0;  // collect all the values
  }
  for (auto& p : xr) xr[p.first] = X++;
  for (auto& p : yr) yr[p.first] = Y++;
  REP(i, n) {
    printf("%d %d\n", xr[A[i].first], yr[A[i].second]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> H >> W >> n;

  solve();
}