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

const int mod = 1e9 + 7, MAXN = 1e5 + 1, MAXM = 17;

int n, L, A[MAXN], adv[MAXN][MAXM];  // advancements

struct Solution {
  Solution() {
    REP(i, n) {
      adv[i][0] = upper_bound(A + i, A + n, A[i] + L) - A - 1;  // farthest city in 1 day
    }
    REPN(j, MAXM - 1) {
      REP(i, n) {
        adv[i][j] = adv[adv[i][j - 1]][j - 1];
        // printf("adv[%d][%d -1]=%d\n", i, j, adv[i][j - 1]);
      }
    }

    // dbgarr2(adv, 10, MAXM);
  }
  int solve(int a, int b) {
    // dbg2(a, b);
    if (a > b) swap(a, b);
    if (a == b) return 0;
    int res = 0;
    while (true) {
      int c = lower_bound(adv[a], adv[a] + MAXM, b) - adv[a] - 1;  // next feasible index < b
      if (c == -1) return res + 1;
      // dbg(c);
      res += 1 << c, a = adv[a][c];
    }
    return -1;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  REP(i, n)
  cin >> A[i];
  cin >> L;
  Solution test;
  int Q, a, b;
  cin >> Q;
  while (Q--) {
    cin >> a >> b;
    auto res = test.solve(--a, --b);
    printf("%d\n", res);
  }
}