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

const int mod = 3, MAXN = 2e5 + 1;

int n, diam_kid[MAXN];
vi adj[MAXN];
struct Solution {
  vi res;
  int t = 1;
  pii diam;
  void solve() {
    res.resize(n), memset(diam_kid, -1, sizeof(diam_kid));
    diam = get_diameter(0);
    // dbg2(diam.first, diam.second);
    dfs(diam.first, -1);
    walk(diam.first, -1);
  }
  void walk(int i, int p) {
    res[i] = t++;
    for (int j : adj[i]) {
      if (j == p || j == diam_kid[i]) continue;
      walk(j, i);
    }
    if (diam_kid[i] != -1) walk(diam_kid[i], i);
    t++;  // revisit
  }
  bool dfs(int i, int p) {  // track which kid leads to the other endpoint of the diameter
    if (i == diam.second) return true;
    for (int j : adj[i]) {
      if (j == p) continue;
      if (dfs(j, i)) diam_kid[i] = j;  // j leads to diam.second
    }
    return diam_kid[i] != -1;
  }
  pii get_diameter(int i) {  // returns diam from the region i is in
    auto p = farthest(i, 0, -1);
    return {farthest(p.second, 0, -1).second, p.second};
  }
  pii farthest(int i, int d, int p) {  // returns {dist, node} farthest from i; d= dist from source node
    pii res = {d, i};
    for (int j : adj[i]) {
      if (j == p) continue;
      res = max(res, farthest(j, d + 1, i));
    }
    return res;
  }
};
void print(vector<int>& nums) {
  for (auto num : nums) cout << num << " ";
  cout << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution test;
  int a, b;
  cin >> n;
  REP(i, n - 1)
  cin >> a >> b,
      adj[--a].push_back(--b), adj[b].push_back(a);
  test.solve();
  print(test.res);
}