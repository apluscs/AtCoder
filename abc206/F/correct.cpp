#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

int grundy(int l, int r, vector<vector<int>> &dp, vector<pi> &seg) {
  if (l >= r) {
    return 0;
  }
  if (dp[l][r] != -1) {
    return dp[l][r];
  }
  vector<bool> kh(128, false);
  for (auto &nx : seg) {
    if (l <= nx.first && nx.second <= r) {
      kh[grundy(l, nx.first, dp, seg) ^ grundy(nx.second, r, dp, seg)] = true;
    }
  }
  for (int i = 0;; i++) {
    if (!kh[i]) {
      dp[l][r] = i;
      break;
    }
  }
  if (dp[l][r]) printf("win @ %d %d\n", l+1, r+1);
  return dp[l][r];
}

int main() {
  int t;
  cin >> t;
  for (int cs = 1; cs <= t; cs++) {
    int n;
    cin >> n;
    vector<pi> seg(n);
    for (int i = 0; i < n; i++) {
      cin >> seg[i].first >> seg[i].second;
      seg[i].first--;
      seg[i].second--;
    }
    vector<vector<int>> dp(100, vector<int>(100, -1));
    if (grundy(0, 99, dp, seg)) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
    }
  }
  return 0;
}