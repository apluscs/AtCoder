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

const int mod = 1e9 + 7, MAXN = 1e5 + 1;

string s;
int n, frq[26];
set<pii> scores[26];

struct Solution {
  pii solve() {
    REP(c, 26) {
      scores[c].insert({1, -1});
    }
    REP(i, n) {
      frq[s[i] - 'a']++;
      REP(c, 26) {
        int x = 2 * frq[c] - i;
        scores[c].insert({x, i});
        auto it = scores[c].lower_bound({x, -1});
        if (it == scores[c].begin()) continue;
        it--;
        int j = it->second;
        if (j < i - 1) return {it->second + 1, i};
        if (it == scores[c].begin()) continue;
        it--;
        return {it->second + 1, i};
      }
    }
    return {-2, -2};
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> s, n = s.length();
  Solution test;
  auto res = test.solve();
  printf("%d %d\n", res.first + 1, res.second + 1);
}