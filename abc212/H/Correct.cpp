#include <bits/stdc++.h>
using namespace std;

#define N (1 << 16)
#define K 16
#define MOD 998244353
#define ll long long
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, a, b) for (int i = a; i <= b; ++i)

ll modpow(ll x, int a) {
  x %= MOD;
  ll re = 1;
  while (a > 0) {
    if (a % 2 == 1) re = (re * x) % MOD;
    x = (x * x) % MOD;
    a /= 2;
  }
  return re;
}

ll inv(ll x) {
  return modpow(x, MOD - 2);
}

ll func(ll x, int n) {
  x %= MOD;
  if (x == 0) return (ll)0;
  if (x == 1) return (ll)n;
  ll re = modpow(x, n) - 1;
  re = (re * x) % MOD;
  re = (re * inv(x - 1)) % MOD;
  return re;
}

int main(void) {
  int p2[K];
  p2[0] = 1;
  rep(i, K - 1) p2[i + 1] = p2[i] * 2;
  int n, k, d;
  ll a[N];
  rep(i, N) a[i] = 0;
  ll x;
  ll ans = 0;

  cin >> n >> k;
  rep(i, k) {
    cin >> x;
    a[x] = 1;
  }
  rep(kk, K) {
    rep(i, p2[K - kk - 1]) {
      d = p2[kk + 1] * i;
      rep(j, p2[kk]) {
        x = (a[d + j] - a[d + p2[kk] + j] + MOD) % MOD;
        a[d + j] = (a[d + j] + a[d + p2[kk] + j]) % MOD;
        a[d + p2[kk] + j] = x;
      }
    }
  }
  rep(i, N) a[i] = func(a[i], n);
  rep(kk, K) {
    rep(i, p2[K - kk - 1]) {
      d = p2[kk + 1] * i;
      rep(j, p2[kk]) {
        x = (a[d + j] - a[d + p2[kk] + j] + MOD) % MOD;
        a[d + j] = (a[d + j] + a[d + p2[kk] + j]) % MOD;
        a[d + p2[kk] + j] = x;
      }
    }
  }
  rep2(i, 1, N - 1) ans += a[i], printf("%d \n", a[i]);
  ans %= MOD;
  ans = (ans * (inv((ll)N))) % MOD;
  cout << ans << endl;

  return 0;
}
