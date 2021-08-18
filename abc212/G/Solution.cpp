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

const int mod = 998244353, MAXN = 1e5;

ll P, divs[MAXN], f_data[MAXN];
int n = 0;
void get_divisors() {
  ll Q = sqrt(P);
  // dbg(Q);
  REPN(i, Q) {
    if (P % i == 0) divs[n++] = i, divs[n++] = P / i;
  }
  if (Q * Q == P) n--;  // ignore the duplicated square root
}
ll f(int i) {                   // how many `a` have divs[i] as their GCD?
  ll g = divs[i], res = P / g;  // overcounting, need to subtract the `a`'s counted by other g multiples of g
  FOR(j, i + 1, n) {
    if (divs[j] % divs[i] == 0) res -= f_data[j];
  }
  return (res % mod + mod) % mod;
}
int solve() {
  get_divisors();
  sort(divs, divs + n);
  ll res = 0;
  FORD(i, n - 1, 0) {
    ll g = divs[i];  // for all `a` with g as GCD, it creates P/g `b`'s; but we want (a,b) pairs
    f_data[i] = f(i);
    res = (res + P / g % mod * f_data[i]) % mod;
  }
  return (res + 1) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> P, P--;
  cout << solve() << endl;
}