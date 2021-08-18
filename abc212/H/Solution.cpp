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
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int mod = 998244353, MAXN = (1 << 16);

using usize = std::size_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

static constexpr u32 Mod = 998244353;

struct modint {
  u32 v;
  modint(const u32 v_ = 0) : v(v_) {}
  friend modint operator+(const modint &l, const modint &r) {
    modint ret(l.v + r.v);
    if (ret.v >= Mod) {
      ret.v -= Mod;
    }
    return ret;
  }
  friend modint operator-(const modint &l, const modint &r) {
    modint ret(l.v - r.v);
    if (l.v < r.v) {
      ret.v += Mod;
    }
    return ret;
  }
  friend modint operator*(const modint &l, const modint &r) {
    return modint(static_cast<u64>(l.v) * r.v % Mod);
  }
};

void walsh_hadamard(std::vector<modint> &a) {
  const usize n = a.size();
  for (usize w = 1; w != n; w *= 2) {
    for (usize k = 0; k != n; k += w * 2) {
      for (usize i = 0; i != w; i += 1) {
        const modint x = a[k + i];
        const modint y = a[k + w + i];
        a[k + i] = x + y;
        a[k + w + i] = x - y;
      }
    }
  }
}

int N, K;
vector<modint> A;

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

int inv(int x) {  // modular inverse of x % mod
  return binpow(x, mod - 2);
}

modint geo_sum(int x, int k) {  // x + x^2 + ... + x^k
  if (x == 0) return modint(0);
  if (x == 1) return modint(k);
  ll re = binpow(x, k) - 1;
  re = (re * x) % mod;
  re = (re * inv(x - 1)) % mod;
  return modint(re);
}

int solve() {
  walsh_hadamard(A);            // now somehow A is encoded s.t. A[i] * A[i] = sum(old_A[j] * old_A[k]) s.t. (j ^ k == i)
  REP(i, MAXN) {                // we need [sum(A[i] + A^2[i] + ... + A^n[i]) for all i]
    A[i] = geo_sum(A[i].v, N);  // but now A^j[i] = A[i]^j
  }
  walsh_hadamard(A);  // H(H(X)) = X
  ll res = 0;
  FOR(i, 1, MAXN) {
    res = (res + A[i].v) % mod;
    // printf("%d \n", A[i].v);
  }
  return res * inv(MAXN) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> K, A.resize(MAXN);
  int temp;
  REP(i, K)
  cin >> temp, A[temp] = modint(1);  // A^j[i] = #ways to achieve an XOR of i when the array has length j
  cout << solve() << endl;
}