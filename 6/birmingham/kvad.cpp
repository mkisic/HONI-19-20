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

const int MAXN = 1000;

int n, m, k, q;
int dist[MAXN][MAXN], ans[MAXN];
int bio[MAXN], bio1[MAXN];

vector <int> v[MAXN];

queue <int> Q;

void bfs2() {
  int cvor, d;
  while (!Q.empty()) {
    cvor = Q.front(); Q.pop();
    d = Q.front(); Q.pop();
    bio1[cvor] = 1;
    ans[cvor] = d;
    FOR(i, 1, n + 1) {
      if (bio1[i] || dist[cvor][i] > (d + 1) * k) continue;
      bio1[i] = 1;
      Q.push(i);
      Q.push(d + 1);
    }
  }
}

void bfs1(int start) {
  queue <int> q;
  memset(bio, 0, sizeof bio);
  q.push(start);
  q.push(0);
  int cvor, d;
  while (!q.empty()) {
    cvor = q.front(); q.pop();
    d = q.front(); q.pop();
    bio[cvor] = 1;
    dist[start][cvor] = d;
    for (auto ncvor : v[cvor]) {
      if (bio[ncvor]) continue;
      bio[ncvor] = 1;
      q.push(ncvor);
      q.push(d + 1);
    }
  }
}

int main() {
  scanf("%d %d %d %d",&n,&m,&q,&k);
  if (n > 120) {
    puts("NE");
    return 0;
  }
  REP(i, q) {
    int x;
    scanf("%d",&x);
    Q.push(x);
    Q.push(0);
    bio1[x] = 1;
  }

  REP(i, m) {
    int a, b;
    scanf("%d %d",&a,&b);
    v[a].pb(b);
    v[b].pb(a);
  }

  FOR(i, 1, n + 1) bfs1(i);

  bfs2();

  FOR(i, 1, n + 1) {
    printf("%d ",ans[i]);
  }
  puts("");

  return 0;
}

