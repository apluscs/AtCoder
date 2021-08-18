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

const int mod = 1e9 + 7, dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}, MAXN = 1e6 + 1;

int sieve[MAXN], L, R;
bool bad[MAXN];
ll N;

struct Solution {
  Solution() {
    gen_sieve();
  }
  ll solve() {
    ll res = 0;
    FORN(x, 2, R) {
      ll fx = get_frqs(x), c = R / x - (L - 1) / x;
      if (x >= L) res -= c * 2 - 1;
      if (fx == -1) continue;  // Mobius = 0
      fx = fx % 2 ? 1 : -1;
      res += c * c * fx;
      // dbg2(x, res);
    }
    return res;
  }
  void gen_sieve() {
    iota(sieve, sieve + MAXN, 0);
    for (int p = 2; p * p < MAXN; p++) {
      if (sieve[p] != p) continue;  // not a prime
      for (int i = p * p; i < MAXN; i += p)
        sieve[i] = p;  // p is smallest pf of i
    }
  }
  int get_frqs(int y) {  // get frq of prime factors of x
    int x = y, res = 0;
    while (x != 1) {
      // dbg2(x, sieve[x]);
      if (bad[x] || !(x / sieve[x] % sieve[x])) {
        bad[y] = true;
        return -1;
      }
      x /= sieve[x], res++;
    }
    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution test;
  cin >> L >> R;
  cout << test.solve() << endl;
}