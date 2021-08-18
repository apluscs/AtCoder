#include <bits/stdc++.h>
using namespace std;

template <int N>
struct sieve {
  std::array<int, N + 1> spf;

  constexpr sieve() {
    spf.fill(0);
    for (int i = 2; i * i <= N; i++) {
      if (spf[i] == 0) {
        for (int j = i * i; j <= N; j += i) {
          if (spf[j] == 0) spf[j] = i;
        }
      }
    }
    for (int i = 2; i <= N; i++) {
      if (spf[i] == 0) {
        spf[i] = i;
      }
    }
  }

  bool is_prime(int x) const {
    return spf[x] == x;
  }

  std::vector<int> primes() const {
    std::vector<int> primes;
    for (int i = 1; i <= N; i++) {
      if (spf[i] == i) {
        primes.push_back(i);
      }
    }
    return primes;
  }

  std::vector<std::pair<int, int>> prime_factors(int x) const {
    std::vector<std::pair<int, int>> factors;
    while (x != 1) {
      if (factors.empty() || factors.back().first != spf[x]) {
        factors.emplace_back(spf[x], 0);
      }
      factors.back().second++;
      x /= spf[x];
    }
    return factors;
  }

  std::vector<int> divisors(int x) const {
    if (x == 1)
      return {1};
    int c = 0, n = x;
    for (; spf[x] == spf[n]; n /= spf[x], c++)
      ;
    std::vector<int> d = divisors(n);
    std::vector<int> res((c + 1) * d.size());
    for (int i = 0, j = 0, p = 1; i <= c; i++, p *= spf[x]) {
      for (int item : d) {
        res[j++] = p * item;
      }
    }
    return res;
  }
};

struct digraph {
  struct edge {
    int u, v;
    edge(int u, int v) : u(u), v(v) {}
  };

  int n, m;
  std::vector<edge> edges;
  std::vector<std::vector<int>> adj;

  digraph() : n(), m() {}
  digraph(int n, int m = 0) : n(n), m(), adj(n) {
    edges.reserve(m);
  }

  int add_edge(int u, int v) {
    edges.emplace_back(u, v);
    adj[u].push_back(m);
    return m++;
  }

  digraph transpose() const {
    digraph rev(n, m);
    for (auto &[u, v] : edges) {
      rev.add_edge(v, u);
    }
    return rev;
  }

  int add_vertex() {
    adj.emplace_back();
    return n++;
  }
};

std::vector<std::vector<int>> find_sccs(const digraph &g) {
  int timer = 0;
  std::vector<int> tin(g.n, -1), low(g.n);

  std::vector<int> all, path;
  all.reserve(g.n), path.reserve(g.n);

  std::vector<std::vector<int>> sccs;
  auto dfs = [&](int u, const auto &self) -> void {
    low[u] = tin[u] = timer++;
    all.push_back(u), path.push_back(u);
    for (int i : g.adj[u]) {
      int v = g.edges[i].v;
      if (tin[v] == -1) {
        self(v, self);
      }
      low[u] = std::min(low[u], low[v]);
    }
    if (low[u] == tin[u]) {
      int sz = std::find(all.rbegin(), all.rend(), u) - all.rbegin();
      sccs.emplace_back(sz + 1);
      for (int i = 0; i < sz; i++) {
        low[all.back()] = g.n;
        sccs.back()[i] = all.back();
        all.pop_back();
      }
      all.pop_back();
      sccs.back().back() = u, low[u] = g.n;
    }
    path.pop_back();
  };

  for (int u = 0; u < g.n; u++) {
    if (tin[u] == -1) {
      dfs(u, dfs);
    }
  }
  std::reverse(sccs.begin(), sccs.end());
  return sccs;
}

constexpr int N = 2000 * 1000;

sieve<N> s;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

  map<int, vector<int>> mp;
  digraph g(2 * n);
  for (int i = 0; i < n; i++) {
    for (auto &[p, c] : s.prime_factors(a[i])) {
      mp[p].push_back(i);
    }
    for (auto &[p, c] : s.prime_factors(b[i])) {
      mp[p].push_back(n + i);
    }
  }

  for (auto &[p, v] : mp) {
    vector<int> y(v.size()), z(v.size());
    for (int i = 0; i + 1 < (int)v.size(); i++) {
      y[i] = g.add_vertex(), g.add_vertex();
      g.add_edge(y[i], v[i] < n ? v[i] + n : v[i] - n); // Y[i] --> ~V[i]
      g.add_edge(v[i], y[i] + 1);
      if (i > 0) {
        g.add_edge(y[i], y[i - 1]); // Y[i] --> Y[i-1]
        g.add_edge(y[i - 1] + 1, y[i] + 1);
      }
    }

    for (int i = (int)v.size() - 1; i > 0; i--) {
      z[i] = g.add_vertex(), g.add_vertex();
      g.add_edge(z[i], v[i] < n ? v[i] + n : v[i] - n); // Z[i] --> ~V[i]
      g.add_edge(v[i], z[i] + 1);
      if (i + 1 < (int)v.size()) {
        g.add_edge(z[i], z[i + 1]); // Z[i] --> Z[i+1]
        g.add_edge(z[i + 1] + 1, z[i] + 1);
      }
    }

    for (int i = 0; i < (int)v.size(); i++) {
      if (i > 0) {
        g.add_edge(v[i], y[i - 1]); // X[i] --> Y[i-1]
        g.add_edge(y[i - 1] + 1, v[i] < n ? v[i] + n : v[i] - n);
      }
      if (i + 1 < (int)v.size()) {
        g.add_edge(v[i], z[i + 1]); // X[i] --> Z[i+1]
        g.add_edge(z[i + 1] + 1, v[i] < n ? v[i] + n : v[i] - n);
      }
    }
  }

  auto sccs = find_sccs(g);

  vector<int> t(g.n);
  for (int i = 0; i < (int)sccs.size(); i++) {
    for (int v : sccs[i]) {
      t[v] = i;
    }
  }

  bool sat = true;
  for (int i = 0; i < g.n; i++) {
    if (i < n) {
      sat &= t[i] != t[i + n];
    } else if (i >= 2 * n && i % 2 == 0) {
      sat &= t[i] != t[i + 1];
    }
  }

  cout << (sat ? "Yes" : "No") << '\n';
  return 0;
}
