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

int n;

struct UnionFind {
  vector <int> v[MAXN];
  int connected[MAXN];
  int par[MAXN];

  void init() {
    REP(i, MAXN) {
      v[i].clear();
      par[i] = i;
      connected[i] = 0;
      v[i].pb(i);
    }
  }

  void merge(int a, int b) {
    a = par[a];
    b = par[b];
    if ((int)v[a].size() < (int)v[b].size()) swap(a, b);

    for (auto x : v[b]) {
      if (par[x - 1] == a) connected[a]++;
      if (par[x + 1] == a) connected[a]++;
      v[a].pb(x);
    }
    for (auto x : v[b]) par[x] = a;
    connected[a] += connected[b];
  }

  int get(int x) {
    x = par[x];
    int ret = ((int)v[x].size() - connected[x]) * 2;
    if (par[1] == x) ret--;
    if (par[n] == x) ret--;
    return ret;
  }
};

UnionFind Uf;

int c[MAXN], d[MAXN];
int cnt[MAXN];

vector <pii> v[MAXN];

void dfs(int cvor, int par, int in) {
  for (auto ncvor : v[cvor]) {
    if (ncvor.fi == par) continue;
    dfs(ncvor.fi, cvor, ncvor.sec);
    Uf.merge(cvor, ncvor.fi);
  }
  if (in != -1) cnt[in] = Uf.get(cvor);
}

int main() {
  scanf("%d",&n);
  REP(i, n - 1) {
    int a, b;
    scanf("%d %d %d %d",&a,&b,&c[i],&d[i]);
    v[a].pb({b, i});
    v[b].pb({a, i});
  }

  Uf.init();
  dfs(1, -1, -1);

  ll sol = 0;
  REP(i, n - 1) {
    sol += min((ll)c[i] * cnt[i], (ll)d[i]);
  }

  printf("%lld\n",sol);
  return 0;
}

