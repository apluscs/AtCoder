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

const int mod = 1e9 + 7, MAXN = 2e5 + 1;

int H, W, A, B, fact[MAXN] = {1, 1};
struct Solution {
  int solve() {
    precompute();
    ll res = ways(0, 0, H - 1, W - 1);
    // dbg(res);
    // dbgarr(fact, 10);
    // dbgarr(invs, 10);
    REP(i, A) {
      int j = B - i - 1;
      if (j < 0) break;
      res -= ways(0, 0, i + H - A, j) * ways(i + H - A, j, H - 1, W - 1) % mod;
      res = (res + mod) % mod;
    }
    return res;
  }
  ll ways(int i1, int j1, int i2, int j2) {
    int di = i2 - i1, dj = j2 - j1;
    // dbg2(di, dj);
    ll res = (ll)fact[di + dj] * inv(fact[di]) % mod * inv(fact[dj]) % mod;
    return res;
  }
  void precompute() {
    for (int i = 2; i < MAXN; ++i)
      fact[i] = (ll)fact[i - 1] * i % mod;
  }
  int inv(int x) {  // modular inverse of x % mod
    return binpow(x, mod - 2);
  }

  ll binpow(ll a, ll b) {  // a ^ b # % mod
    a %= mod;
    ll res = 1;
    while (b > 0) {
      if (b & 1)
        res = res * a % mod;
      a = a * a % mod;
      b >>= 1;
    }
    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> H >> W >> A >> B;
  Solution test;
  cout << test.solve() << endl;
}