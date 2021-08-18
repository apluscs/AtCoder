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
#define dbg3(x, y, z) cout << (#x) << " is " << (x) << ", " << (#y) << " is " << y << ", " << (#z) << " is " << z << endl;
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

const int mod = 1e9 + 7, MAXN = 1e6 + 2, ALPHA = 256;

int n, frq[MAXN], lcp[MAXN];
ll L[MAXN], R[MAXN], res[MAXN];
string s;

vi suffix_array() {
  vector<int> p(n), c(n);  // n = length of s
  // dbg(s);
  memset(frq, 0, sizeof(frq));
  REP(i, n)
  frq[s[i]]++;
  FOR(i, 1, ALPHA)
  frq[i] += frq[i - 1];
  REP(i, n)
  p[--frq[s[i]]] = i;  // p = ordered permutation of s
  c[p[0]] = 0;         // p[0] = index in s, c is class wrt original index
  int classes = 1;
  FOR(i, 1, n) {
    if (s[p[i]] != s[p[i - 1]]) classes++;
    c[p[i]] = classes - 1;  // c[i] = what class s[i] is
  }
  vector<int> pn(n), cn(n);
  for (int h = 0; (1 << h) < n; ++h) {
    for (int i = 0; i < n; i++) {
      pn[i] = p[i] - (1 << h);
      if (pn[i] < 0)
        pn[i] += n;
    }
    memset(frq, 0, sizeof(frq));
    for (int i = 0; i < n; i++)
      frq[c[pn[i]]]++;
    for (int i = 1; i < classes; i++)
      frq[i] += frq[i - 1];
    for (int i = n - 1; i >= 0; i--)
      p[--frq[c[pn[i]]]] = pn[i];
    classes = 1, cn[p[0]] = 0;
    // dbg(h);
    for (int i = 1; i < n; i++) {
      pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
      pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
      if (cur != prev)
        ++classes;
      cn[p[i]] = classes - 1;
    }
    c.swap(cn);
  }
  return p;  // p[i] = index of suffix that has order i
}

void lcps_construction(vi& p) {  // calculate adjacent LCPs
  int rank[MAXN], k = 0;         // rank[i] = index of s[i] in suffs
  REP(i, n)
  rank[p[i]] = i;
  REP(i, n) {  // index in s
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = p[rank[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k])
      k++;
    lcp[rank[i]] = k;  // lcp[i] = lcp of s[p[i]], s[p[i]+1]
    if (k) k--;
  }
}

void solve() {
  auto suff = suffix_array();
  lcps_construction(suff), n--;
  REP(i, n)
  lcp[i] = lcp[i + 1], suff[i] = suff[i + 1] - 1;
  // dbgitem(suff);
  // dbgarr(lcp, n);
  stack<int> st;                                              // of LCP vals
  REP(i, n - 1) {                                             // update L[i+1]
    while (!st.empty() && lcp[i] <= lcp[st.top()]) st.pop();  // mono inc
    ll x = st.empty() ? i + 1 : i - st.top();
    // dbg2(i, x);
    L[i + 1] = x * lcp[i] + (st.empty() ? 0 : L[st.top() + 1]);
    st.push(i);  // new minimum takes over
  }
  st = stack<int>();
  FORD(i, n - 1, 0) {
    while (!st.empty() && lcp[i] <= lcp[st.top()]) st.pop();  // mono inc
    ll x = st.empty() ? n - i : st.top() - i;
    R[i] = x * lcp[i] + (st.empty() ? 0 : R[st.top()]);
    st.push(i);
  }
  // dbgarr(L, n);
  // dbgarr(R, n);
  REP(i, n) {
    int j = suff[i];
    res[j] = L[i] + R[i] + n - j;
  }
  REP(i, n) {
    printf("%lld\n", res[i]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> s, s = "$" + s, n++;
  solve();
}