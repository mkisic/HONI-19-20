#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1e5 + 10;
const int INF = 1e9;

int n, m, q, k;
int dist[MAXN];

vector<int> graf[MAXN];
vector<int> sastanak;

void unos() {
  scanf("%d %d %d %d", &n, &m, &q, &k);
  REP(i, q) {
    int x;
    scanf("%d", &x);
    sastanak.push_back(x);
  }
  REP(i, m) {
    int a, b;
    scanf("%d %d", &a, &b);
    graf[a].push_back(b);
    graf[b].push_back(a);
  }
}

void bfs() {
  REP(i, n + 1) dist[i] = INF;
  queue<int> q;
  for(auto x : sastanak) {
    dist[x] = 0;
    q.push(x);
  }
  while(!q.empty()) {
    int sad = q.front();
    q.pop();
    for(auto kamo : graf[sad]) {
      if(dist[sad] + 1 < dist[kamo]) {
        dist[kamo] = dist[sad] + 1;
        q.push(kamo);
      }
    }
  }
}

void zavrsi() {
  vector<int> pos(n + 1);
  REP(i, n + 10) {
    llint sad = (llint) k * ((llint) i * (i + 1) / 2) + 1;
    if(sad <= n)
      pos[sad] = 1;
    else
      break;
  }
  vector<int> f;
  f.push_back(0);
  FOR(i, 1, n + 1)
    f.push_back(f.back() + pos[i]);
  FOR(i, 1, n + 1) {
    printf("%d", f[dist[i]]);
    if(i < n) printf(" ");
    else printf("\n");
  }
}

int main() {
  unos();
  bfs();
  zavrsi();
  return 0;
}

