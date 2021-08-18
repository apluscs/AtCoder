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
#define dbg3(x, y, z) cout << (#x) << " is " << (x) << ", " << (#y) << " is " << y << ", " << (#z) << " is " << z << endl;
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

const int MAXN = 502, inf = 1e9, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int H, W, dist[MAXN][MAXN];
bool vis[MAXN][MAXN];
string grid[MAXN];

bool out(int i, int j) { return i <= -1 || i >= H || j <= -1 || j >= W; }

int solve() {
  deque<pii> q;
  REP(i, H)
  fill(dist[i], dist[i] + MAXN, inf);
  q.emplace_front(0, 0), dist[0][0] = 0;
  while (!q.empty()) {
    auto v = q.front();
    q.pop_front();
    int i = v.first, j = v.second;
    // if (vis[i][j]) continue;
    vis[i][j] = true;
    FOR(di, -2, 3) {
      FOR(dj, -2, 3) {
        int ni = i + di, nj = j + dj, w = abs(di) + abs(dj) > 1;
        // dbg3(ni, nj, w);
        if (out(ni, nj) || abs(di) + abs(dj) == 4) continue;
        w = w || grid[ni][nj] == '#';                  // or adjacent and blocked
        if (dist[ni][nj] <= dist[i][j] + w) continue;  // not impoved
        dist[ni][nj] = dist[i][j] + w;
        if (w)
          q.emplace_back(ni, nj);
        else
          q.emplace_front(ni, nj);  // smaller ones go to front
      }
    }
  }
  // dbgarr2(dist, H, W);
  return dist[H - 1][W - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> H >> W;
  REP(i, H)
  cin >> grid[i];
  cout << solve() << endl;
}