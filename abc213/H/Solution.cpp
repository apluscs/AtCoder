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

const int mod = 998244353, MAXN = 10, MAXT = 4e4 + 1;

int n, m, T, edges[MAXN][2];
ll dp[MAXN][MAXT];  // dp[i][j] = #ways to reach node i in exactly T miles
vi adj[MAXN][MAXN];

using uint = unsigned int;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T>
using V = vector<T>;
template <class T>
using VV = V<V<T>>;

template <uint MD>
struct ModInt {
  using M = ModInt;
  const static M G;
  uint v;
  ModInt(ll _v = 0) { set_v(_v % MD + MD); }
  M& set_v(uint _v) {
    v = (_v < MD) ? _v : _v - MD;
    return *this;
  }
  explicit operator bool() const { return v != 0; }
  M operator-() const { return M() - *this; }
  M operator+(const M& r) const { return M().set_v(v + r.v); }
  M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
  M operator*(const M& r) const { return M().set_v(ull(v) * r.v % MD); }
  M operator/(const M& r) const { return *this * r.inv(); }
  M& operator+=(const M& r) { return *this = *this + r; }
  M& operator-=(const M& r) { return *this = *this - r; }
  M& operator*=(const M& r) { return *this = *this * r; }
  M& operator/=(const M& r) { return *this = *this / r; }
  bool operator==(const M& r) const { return v == r.v; }
  M pow(ll n) const {
    M x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  M inv() const { return pow(MD - 2); }
  friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
using Mint = ModInt<998244353>;
template <>
const Mint Mint::G = Mint(3);

template <class Mint>
void nft(bool type, V<Mint>& a) {
  int n = int(a.size()), s = 0;
  while ((1 << s) < n) s++;
  assert(1 << s == n);

  static V<Mint> ep, iep;
  while (int(ep.size()) <= s) {
    ep.push_back(Mint::G.pow(Mint(-1).v / (1 << ep.size())));
    iep.push_back(ep.back().inv());
  }
  V<Mint> b(n);
  for (int i = 1; i <= s; i++) {
    int w = 1 << (s - i);
    Mint base = type ? iep[i] : ep[i], now = 1;
    for (int y = 0; y < n / 2; y += w) {
      for (int x = 0; x < w; x++) {
        auto l = a[y << 1 | x];
        auto r = now * a[y << 1 | x | w];
        b[y | x] = l + r;
        b[y | x | n >> 1] = l - r;
      }
      now *= base;
    }
    swap(a, b);
  }
}

template <class Mint>
V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  int lg = 0;
  while ((1 << lg) < n + m - 1) lg++;
  int z = 1 << lg;
  auto a2 = a, b2 = b;
  a2.resize(z);
  b2.resize(z);
  nft(false, a2);
  nft(false, b2);
  for (int i = 0; i < z; i++) a2[i] *= b2[i];
  nft(true, a2);
  a2.resize(n + m - 1);
  Mint iz = Mint(z).inv();
  for (int i = 0; i < n + m - 1; i++) a2[i] *= iz;
  return a2;
}

V<Mint> get_vec(int i, int L, int R) {  // [L, R]
  V<Mint> res(R - L + 1);
  FOR(j, L, R + 1)
  res[j - L].v = dp[i][j];
  return res;
}

V<Mint> get_vec(vi& v, int L, int R) {  // [L, R]
  V<Mint> res(R - L + 1);
  FOR(j, L, R + 1)
  res[j - L].v = v[j];
  return res;
}

void online_fft(int L, int R) {  // fills in dp[i][L:R] for all i
  if (L >= R) return;            // nothing to give contributions
  int M = (L + R) / 2;
  // dbg2(L, R);
  online_fft(L, M);

  REP(i, m) {
    int a = edges[i][0], b = edges[i][1];
    auto A = get_vec(a, L, M), B = get_vec(b, L, M), F = get_vec(adj[a][b], 0, R - L);
    auto C = multiply(A, F);  // convolute, so C[i] = all ways to get `a` with exactly L+i miles
    FOR(i, M + 1, R + 1)
    dp[b][i] = (dp[b][i] + C[i - L].v) % mod;
    C = multiply(B, F);  // symmetry
    FOR(i, M + 1, R + 1)
    dp[a][i] = (dp[a][i] + C[i - L].v) % mod;
  }
  online_fft(M + 1, R);
}

int solve() {
  dp[0][0] = 1, online_fft(0, T);
  return dp[0][T];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> T;
  int a, b;
  REP(i, m) {
    cin >> a >> b, a--, b--, adj[a][b].resize(T), edges[i][0] = a, edges[i][1] = b;
    REPN(j, T)
    cin >> adj[a][b][j];  // not at (b,a) bc we won't use it
  }
  cout << solve() << endl;
}