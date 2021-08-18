#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>l_l;

set<vector<string>>used;//boards already searched
vector<string>s;//current board
ll answer=0;//resulting answer
ll n;
vector<ll> dx={1,0,-1,0};
vector<ll> dy={0,1,0,-1};

bool valid(ll x,ll y){
    return 0<=x && x<=n-1 && 0<=y && y<=n-1;//If (x,y) is in the board
}

void dfs(ll num){
    //num: how many red squares do we have to place?

    if(used.find(s)!=used.end()){
        return;//We've already searched this, skipping
    }
    used.insert(s);//Add the current board to the set of already-searched boards

    if(num==0){
        answer++;//This board satisfies the condition; add 1 to answer
        return; //We don't place red squares anymore
    }

    vector<l_l>next;//candidates of squares to place a red square next

    for(int i=0;i<=n-1;i++){
        for(int j=0;j<=n-1;j++){
            //We can put a new red square to (i, j) if and only if
            //s[i][j] is a white square ('.') and there is a red square ('@') next to s[i][j]

            if(s[i][j]=='.'){
                bool flag=false;
                for(int z=0;z<=3;z++){
                    ll nxt_i=i+dx[z];
                    ll nxt_j=j+dy[z];
                    if(valid(nxt_i,nxt_j) && s[nxt_i][nxt_j]=='@'){
                        flag=true;//If there is a red square next to (i, j), set flag to true
                    }
                }
                if(flag){
                    next.push_back({i,j});//add (i, j) as the next candidate of red square
                }
            }
        }
    }
    for(l_l pos:next){
        s[pos.first][pos.second]='@';//paint red
        dfs(num-1);                  //advance DFS
        s[pos.first][pos.second]='.';//clean up
    }
}

signed main(){
    ll k;cin>>n>>k;
    s.resize(n);
    for(int i=0;i<=n-1;i++)cin>>s[i];

    for(int i=0;i<=n-1;i++){
        for(int j=0;j<=n-1;j++){
            //We paint Square (i, J) first
            if(s[i][j]=='.'){
                s[i][j]='@';//paint red
                dfs(k-1);   //start DFS
                s[i][j]='.';//clean up
            }
        }
    }
    cout<<answer<<endl;
    return 0;
}
