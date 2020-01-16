#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 2e5 + 10;

int q, n, t;
int d[MAXN], f[MAXN], rxor[MAXN];

vector<pair<int, int>> v[MAXN];

void dfs(int node, int dad, int xval) {
  d[node] = ++t;
  rxor[node] = xval;
  for (const auto &p : v[node]) {
    int nxt = p.first;
    int w = p.second;
    if (nxt == dad) continue;
    dfs(nxt, node, xval ^ w);
  }
  f[node] = t;
}

int query(int a, int b) {
  t = 0;
  dfs(0, -1, 0);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    if (d[i] < d[b] || d[i] > f[b]) continue;
    ret = max(ret, rxor[a] ^ rxor[i]);
  }
  return ret;
}

int main(void) {
  n = 1;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    char s[10];
    scanf("%s", s);
    if (s[0] == 'A') {
      int x, y;
      scanf("%d%d", &x, &y); --x;
      v[x].emplace_back(n, y);
      v[n].emplace_back(x, y);
      ++n;
    } else {
      int a, b;
      scanf("%d%d", &a, &b); --a; --b;
      printf("%d\n", query(a, b));
    }
  }
  return 0;
}
