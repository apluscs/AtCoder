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

const int mod = 1e9 + 7, MAXN = 1e5 + 1, MAXL = 18;

int n, Bs[MAXN][4], m, lift[MAXN][MAXL];
map<int, int> Ss[MAXN];  // stations
string solve(int s, int st, int et) {
  auto it = Ss[s].lower_bound(st);
  if (it == Ss[s].end()) return to_string(s);  // stuck at s
  int b = it->second;                          // first bus
  if (Bs[b][2] >= et) return to_string(s);
  // dbg2(st, et);
  while (true) {
    int nb = b, tb;  // next bus, temp bus
    FORD(j, MAXL - 1, 1) {
      tb = lift[b][j];
      if (Bs[tb][2] < et) {  // bus starts before end time
        nb = tb;
        break;
      }
    }
    if (nb == b) break;  // cannot advance another bus
    // dbg2(b, nb);
    b = nb;
  }

  if (Bs[b][3] >= et) return to_string(Bs[b][0]) + " " + to_string(Bs[b][1]);
  return to_string(Bs[b][1]);  // just the end city
}

void presolve() {
  REP(i, m)
  lift[i][0] = i;  // in 1 step, last bus is yourself
  REPN(j, MAXL - 1) {
    REP(i, m) {
      int s = Bs[lift[i][j - 1]][1], t = Bs[lift[i][j - 1]][3];  // station you land on, time you land there
      auto k = Ss[s].lower_bound(t);                             // next bus after landing
      if (k == Ss[s].end()) {
        lift[i][j] = lift[i][j - 1];  // nowhere else to go afterwards, just stay put
      } else
        lift[i][j] = lift[k->second][j - 1];
    }
  }
  // dbgarr2(lift, m, 6);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int Q, v, st, et;
  cin >> n >> m >> Q;
  REP(i, m) {
    cin >> Bs[i][0] >> Bs[i][1] >> Bs[i][2] >> Bs[i][3];
    Ss[Bs[i][0]][Bs[i][2]] = i;  // map start time to bus index
  }
  presolve();
  while (Q--) {
    cin >> st >> v >> et;
    printf("%s\n", solve(v, st, et).c_str());
  }
}