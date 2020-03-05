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

const int MAXN = 100100;

int n, m, k, q;
int dist[MAXN], ans[MAXN];
int bio[MAXN];

vector <int> v[MAXN];

queue <int> Q;

void bfs() {
  int cvor;
  while (!Q.empty()) {
    cvor = Q.front();
    Q.pop();
    for (auto ncvor : v[cvor]) {
      if (bio[ncvor]) continue;
      bio[ncvor] = 1;
      Q.push(ncvor);
      dist[ncvor] = dist[cvor] + 1;
    }
  }
}

int main() {
  scanf("%d %d %d %d",&n,&m,&q,&k);
  REP(i, q) {
    int x;
    scanf("%d",&x);
    if (!bio[x]) Q.push(x);
    bio[x] = 1;
  }

  REP(i, m) {
    int a, b;
    scanf("%d %d",&a,&b);
    v[a].pb(b);
    v[b].pb(a);
  }

  bfs();

  int pt = 1, j = 1;
  while (pt < MAXN) {
    FOR(i, pt, pt + j * k) {
      if (i < MAXN) ans[i] = j;
    }
    pt += j * k;
    j++;
  }

  FOR(i, 1, n + 1) {
    printf("%d ",ans[dist[i]]);
  }
  puts("");

  return 0;
}

