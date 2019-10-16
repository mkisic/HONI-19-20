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

const int MAXN = 510;

int n, m;
ll p[MAXN];

int bio[MAXN];
int in[MAXN];
vector <int> v[MAXN];

vector <pair <ll, int> > T;

void rootaj(int cvor, int par) {
  bio[cvor] = 1;
  T.pb({p[cvor], cvor});
  for (auto ncvor : v[cvor]) {
    if (ncvor != par) {
      rootaj(ncvor, cvor);
    }
  }
}

vector <int> poc;

int ans[MAXN];
int val[MAXN];

void dijkstra() {
  priority_queue <pair <pair <int, ll>, int> > q;
  for (auto x : poc) {
    bio[x] = 1;
    q.push({{0, -p[x]}, x});
  }
  int cnt = 0;
  int cvor;
  ll sum = 0;
  REP(i, MAXN) val[i] = 1;
  while (!q.empty()) {
    cvor = q.top().sec;
    sum -= q.top().fi.sec;
    cnt += q.top().fi.fi;
    q.pop();
    ans[cnt] = sum;
    for (auto ncvor : v[cvor]) {
      if (bio[ncvor]) continue;
      bio[ncvor] = 1;
      q.push({{val[cvor] + val[ncvor], -p[ncvor]}, ncvor});
      val[cvor] = 0;
      val[ncvor] = 0;
    }
  }
}


int main() {
  scanf("%d %d",&n,&m);
  REP(i, n) scanf("%lld",&p[i]);
  REP(i, m) {
    int a, b;
    scanf("%d %d",&a,&b);
    a--; b--;
    v[a].pb(b);
    v[b].pb(a);
    in[a]++;
    in[b]++;
  }

  REP(i, n) {
    if (!bio[i]) {
      T.clear();
      rootaj(i, n);
      v[n].pb(i);
      sort(all(T));
      poc.pb(T[0].sec);
    }
  }

  in[n] = (int)v[n].size() + 1;

  memset(bio, 0, sizeof bio);

  dijkstra();

  int q;
  cin >> q;
  REP(i, q) {
    ll s;
    cin >> s;
    int lo = 0, hi = n, mid;
    while (lo != hi) {
      mid = (lo + hi + 1) / 2;
      if (ans[mid] <= s) lo = mid;
      else hi = mid - 1;
    }
    if (lo == 1) lo = 0;
    printf("%d\n",lo);
  }
  return 0;
}
