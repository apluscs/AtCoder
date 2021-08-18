#include <bits/stdc++.h>
using namespace std;

size_t gcd(size_t a, size_t b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  size_t n, m;
  cin >> n >> m;

  multimap<size_t, size_t> doge;
  for (size_t i = 0; i < m; i++) {
    size_t a, c;
    cin >> a >> c;
    doge.emplace(c, a);
  }

  size_t price = 0;
  for (auto [cost, offset] : doge) {
    size_t moo = gcd(n, offset);
    price += cost * (n - moo);
    n = moo;
    if (n == 1) {
      cout << price << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}
