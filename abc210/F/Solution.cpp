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

const int mod = 1e9 + 7, MAXN = 3e4 + 1, MAXV = 2e6;
int n, A[MAXN][2], sieve[MAXV + 2], X[MAXN * 2];
vi has[MAXV];  // for each prime, what are the bool vars that have it?

struct TwoSat {
  int N, E;
  vector<vi> gr;
  vi values;  // 0 = false, 1 = true

  TwoSat(int m = 0) : N(m), gr(2 * m) {}

  int addVar() {  // (optional)
    gr.emplace_back();
    gr.emplace_back();
    return N++;
  }

  void either(int f, int j) {
    f = max(2 * f, -1 - 2 * f);
    j = max(2 * j, -1 - 2 * j);
    gr[j ^ 1].push_back(f);
    gr[f ^ 1].push_back(j);
    // dbg2(f, (f ^ 1));
    // dbg2(j, (j ^ 1));
  }
  void implies(int f, int j) {
    // string k = j < 0 ? "-" + to_string(~j) : to_string(j);
    // dbg2(f, k);
    f = max(2 * f, -1 - 2 * f);
    j = max(2 * j, -1 - 2 * j);
    gr[f].push_back(j);
  }

  void atMostOne(const vi& li) {  // (optional)
    if (sz(li) <= 1) return;
    int cur = ~li[0];
    rep(i, 2, sz(li)) {
      int next = addVar();
      either(cur, ~li[i]);
      either(cur, next);
      either(~li[i], next);
      cur = ~next;
    }
    either(cur, ~li[1]);
  }

  vi val, comp, z;
  int time = 0;
  int dfs(int i) {
    int low = val[i] = ++time, x;
    z.push_back(i);
    // dbg(i);
    // dbgitem(gr[i]);
    for (int e : gr[i])
      if (!comp[e])
        low = min(low, val[e] ?: dfs(e));
    if (low == val[i]) do {
        x = z.back();
        z.pop_back();
        comp[x] = low;
        if (values[x >> 1] == -1)
          values[x >> 1] = x & 1;
      } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    values.assign(N, -1);
    val.assign(2 * N, 0);
    // dbgitem(gr[2]);
    comp = val;
    rep(i, 0, 2 * N) if (!comp[i]) dfs(i);
    rep(i, 0, N) if (comp[2 * i] == comp[2 * i + 1]) {
      return 0;
    }
    return 1;
  }
};

void gen_sieve() {
  iota(sieve + 1, sieve + MAXV + 1, 1);
  for (int p = 2; p * p <= MAXV; p++) {
    if (sieve[p] != p) continue;  // not a prime
    for (int i = p * p; i <= MAXV; i += p)
      sieve[i] = p;  // p is smallest pf of i
  }
}

vi get_frqs(int x) {  // get prime factors of x
  set<int> res;
  while (x != 1) {
    res.insert(sieve[x]);
    x /= sieve[x];
  }
  return vi(res.begin(), res.end());
}

int rev(int x) {
  return x < n ? x + n : x - n;
}

string solve() {
  gen_sieve();
  TwoSat ts(2 * n);
  REP(i, n) {
    auto frqs = get_frqs(A[i][0]);
    for (int f : frqs) has[f].push_back(i);
    frqs = get_frqs(A[i][1]);
    for (int f : frqs) has[f].push_back(~i);
  }
  // dbgarr(X, 2 * n);
  REP(p, MAXV) {  // all boolean vars corresponding to a prime
    auto& X = has[p];
    ts.atMostOne(X);
  }

  string res = ts.solve() ? "Yes" : "No";
  // dbgitem(ts.values);
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  REP(i, n)
  cin >> A[i][0] >> A[i][1];
  cout << solve() << endl;
}