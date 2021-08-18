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

const int inf = 1e9 + 7, MAXN = 1e5 + 1, MAXM = 4e5;

int n, V = 0, Q, res[MAXN];
vi Qs[MAXN], verts[MAXM];  // verts[i] = x, y1, y2, delta
vector<vi> polys[MAXN];

struct Node {
  int start, mid, end, len, sum = 0, lazy = 0;  // lazy range update pending. INDIVIDUAL element changes pending on my
  Node *left = nullptr, *right = nullptr;

  Node(int s, int e) {
    start = s;
    end = e;
    mid = (s + e) >> 1;
    len = e + 1 - s;
  }

  int update(int f, int t, int delta) {  // set
    if (f > t)
      return sum + lazy * len;  // don't ruin others
    if (f == start && t == end)
      return sum + (lazy += delta) * len;

    _emergency();
    sum = left->update(max(f, start), min(t, mid), delta) + right->update(max(f, mid + 1), min(t, end), delta);
    return sum + lazy * len;
  }

  int query(int f, int t) {
    if (f > t)
      return 0;  // don't interfere

    if (f == start && t == end)
      return lazy * len + sum;

    _emergency();

    return left->query(max(f, start), min(t, mid))       // left
           + right->query(max(f, mid + 1), min(t, end))  // right;
           + (t + 1 - f) * lazy;                         // quantity * pending on my level
  }

  void _emergency() {       // internal func
    if (left == nullptr) {  // emergency build
      left = new Node(start, mid);
      right = new Node(mid + 1, end);
    }
  }
};

void prep(vector<vi>& poly) {
  Node* root = new Node(0, MAXN);
  for (auto& vert : poly) {
    int y1 = vert[1], y2 = vert[2] - 1, d = root->query(y1, y2);  // d = 1 if present alr; otherwise 0
    verts[V++] = {vert[0], y1, y2, d ? -1 : 1};
    if (d)
      root->update(y1, y2, -1);
    else
      root->update(y1, y2, 1);
  }
}

void solve() {
  REP(i, n) {
    prep(polys[i]);
  }
  Node* root = new Node(0, MAXN);
  int qi = 0;
  sort(verts, verts + V);
  for (int v = 0; qi != Q;) {
    while (v != V) {  // catch up to the query
      int x = verts[v][0], y1 = verts[v][1], y2 = verts[v][2];
      if (x > Qs[qi][0]) break;  // processed everything needed at this point
      // printf("x=%d, y1=%d, y2=%d, d=%d\n", x, y1, y2, verts[v][3]);
      root->update(y1, y2, verts[v++][3]);
    }
    // dbg(Qs[qi][1]);
    res[Qs[qi++][2]] = root->query(Qs[qi][1], Qs[qi][1]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  int x1, y1, x2, y2, m;
  REP(i, n) {
    cin >> m;
    do {
      cin >> x1 >> y1 >> x2 >> y2, polys[i].push_back({x1, min(y1, y2), max(y1, y2)});
      m -= 2;
    } while (m);
    sort(polys[i].begin(), polys[i].end());
  }
  cin >> Q;
  REP(i, Q)
  Qs[i].resize(3), cin >> Qs[i][0] >> Qs[i][1], Qs[i][2] = i;
  sort(Qs, Qs + Q);
  solve();
  REP(i, Q)
  printf("%d\n", res[i]);
}