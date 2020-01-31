#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

const int MAXN = 200100;
const int LOG = 19;

int n, lca[LOG][MAXN];
int dub[MAXN];

int c[MAXN], d[MAXN];
int cnt[MAXN], p[MAXN], dp[MAXN];

vector <pii> v[MAXN];

void dfs(int cvor, int par, int d) {
  dub[cvor] = d;
  for (auto ncvor : v[cvor]) {
    if (ncvor.fi == par) continue;
    dfs(ncvor.fi, cvor, d + 1);
    lca[0][ncvor.fi] = cvor;
  }
}

int get_lca(int a, int b) {
  if (dub[a] < dub[b]) swap(a, b);
  for (int i = LOG - 1; i >= 0; i--) {
    if (dub[a] - (1 << i) >= dub[b]) {
      a = lca[i][a];
    }
  }

  if (a == b) return a;
  
  for (int i = LOG - 1; i >= 0; i--) {
    if (lca[i][a] != lca[i][b]) {
      a = lca[i][a];
      b = lca[i][b];
    }
  }
  return lca[0][a];
}

void rek(int cvor, int par, int in) {
  for (auto ncvor : v[cvor]) {
    if (ncvor.fi == par) continue;
    rek(ncvor.fi, cvor, ncvor.sec);
    dp[cvor] += dp[ncvor.fi];
  }
  dp[cvor] += p[cvor];
  if (in != -1) cnt[in] = dp[cvor];
}

int main() {
  scanf("%d",&n);
  REP(i, n - 1) {
    int a, b;
    scanf("%d %d %d %d",&a,&b,&c[i],&d[i]);
    v[a].pb({b, i});
    v[b].pb({a, i});
  }

  dfs(1, -1, 0);

  FOR(i, 1, LOG) {
    FOR(j, 1, n + 1) {
      lca[i][j] = lca[i - 1][lca[i - 1][j]];
    }
  }

  FOR(i, 1, n) {
    int l = get_lca(i, i + 1);
    p[i]++;
    p[i + 1]++;
    p[l] -= 2;
  }

  rek(1, -1, -1);

  ll sol = 0;
  REP(i, n - 1) {
    sol += min((ll)c[i] * cnt[i], (ll)d[i]);
  }

  printf("%lld\n",sol);
  return 0;
}

