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
#define FOREACH(a, b) for (auto &(a) : (b))
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

const int mod = 3, MAXN = 4e5 + 1;

int n, A[MAXN], fact[mod];
struct Solution {
  char solve() {
    int res = 0;
    fact[0] = 1;
    REPN(i, mod - 1) {
      fact[i] = (i * fact[i - 1]) % mod;
    }
    REP(i, n) {
      res = (res + A[i] * choose(n - 1, i)) % mod;
    }
    if (n % 2 == 0) res = (3 - res) % mod;
    return res == 1 ? 'B' : res == 0 ? 'R'
                                     : 'W';
  }
  int factmod(int x) {  // modified factorial of x % mod, where every p that appeared as a factor --> 1
    int res = 1;
    while (x > 1) {
      if ((x / mod) % 2)
        res = mod - res;
      res = res * fact[x % mod] % mod;
      x /= mod;
    }
    return res;
  }
  int multiplicity_factorial(int x) {  // how many times does x appear as a factor in the modified factorial?
    int count = 0;
    do {
      x /= mod;
      count += x;
    } while (x);
    return count;
  }
  int choose(int x, int y) {  // x choose y % mod
    int mx = multiplicity_factorial(x), my = multiplicity_factorial(y), mxy = multiplicity_factorial(x - y), res = factmod(x) * factmod(y) * factmod(x - y);
    if (mx > my + mxy) {
      return 0;
    }
    return res % mod;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution test;
  string s;
  cin >> n >> s;
  REP(i, n)
  A[i] = s[i] == 'B' ? 1 : s[i] == 'R' ? 0
                                       : 2;
  cout << test.solve() << endl;
}