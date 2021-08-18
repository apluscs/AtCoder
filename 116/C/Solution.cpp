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

const int mod = 998244353, MAXN = 2e5 + 1, MAXH = 19;

int n, m, sieve[MAXN], inv[MAXN], choose[MAXN + MAXH][MAXH];
ll facts[MAXN] = {1};
struct Solution {
  int solve() {
    gen_sieve(), gen_choose();
    ll res = 0;
    REPN(i, m) {  // ending value = i
      vi frqs = get_frqs(i);
      // dbgitem(frqs);
      ll x = 1;
      for (int f : frqs) x = (x * choose[n + f - 1][f]) % mod;
      // dbg2(i,x);
      res = (res + x) % mod;
    }
    return res;
  }

  vi get_frqs(int x) {  // get frq of prime factors of x
    map<int, int> frq;
    vi res;
    while (true) {
      if (sieve[x] == 1) break;
      frq[sieve[x]]++, x /= sieve[x];
    }
    for (auto& p : frq) res.push_back(p.second);
    return res;
  }
  void gen_sieve() {
    iota(sieve + 1, sieve + MAXN, 1);
    for (int p = 2; p * p <= m; p++) {
      if (sieve[p] != p) continue;  // not a prime
      for (int i = p * p; i <= m; i += p)
        sieve[i] = p;  // p is smallest pf of i
    }
    // dbgarr(sieve,m+1);
  }
  void gen_choose() {
    REP(i, n + MAXH)
    choose[i][0] = 1;  // one way to choose 0
    REPN(i, n + MAXH) {
      REPN(j, min(i, MAXH - 1)) {
        choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution test;
  cin >> n >> m;
  cout << test.solve() << endl;
}