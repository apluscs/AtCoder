#include <bits/stdc++.h>
#define rep(i,n) for(int i = 0; i < (n); i++)
using namespace std;
typedef long long ll;

ll dp[5050][5050], mod = 998244353;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    int N,M,K; cin >> N >> M >> K;
    vector<vector<int>> G(N);
    rep(i,M){
        int u,v; cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dp[0][0] = 1;
    rep(i,K){
        ll sum = 0;
        rep(j,N) sum = (sum + dp[i][j]) % mod;
        rep(j,N){
            dp[i + 1][j] = (sum - dp[i][j] + mod) % mod;
            for(int v : G[j]) dp[i + 1][j] = (dp[i + 1][j] - dp[i][v] + mod) % mod;
        }
    }
    cout << dp[K][0] << endl;
}