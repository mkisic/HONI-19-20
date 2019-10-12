#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1010;

bool bio[MAXN][MAXN];

char grid[MAXN][MAXN];

int R, S, sol;
int dr[] = {0, 1, 0, -1};
int ds[] = {1, 0, -1, 0};

inline bool check(int r, int s) {
  return r >= 0 && r < R && s >= 0 && s < S && !bio[r][s];
}

void bfs(int r, int s) {
  ++sol;
  queue<pair<int, int>> Q;
  bio[r][s] = true;
  Q.push({r, s});
  while (!Q.empty()) {
    auto curr = Q.front(); Q.pop();
    for (int i = 0; i < 4; ++i) {
      int rr = curr.first + dr[i], ss = curr.second + ds[i];
      if (check(rr, ss) && grid[rr][ss] == grid[r][s]) {
        bio[rr][ss] = true;
        Q.push({rr, ss});
      }
    }
  }
}

int main(void) {
  scanf("%d%d", &R, &S);
  for (int i = 0; i < R; ++i) scanf("%s", grid[i]);

  for (int i = 0; i < R; ++i)
    for (int j = 0; j < S; ++j)
      if (grid[i][j] != '*' && !bio[i][j])
        bfs(i, j);

  printf("%d\n", sol);
  return 0;
}
