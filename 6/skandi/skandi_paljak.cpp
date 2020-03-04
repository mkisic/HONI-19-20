#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 505;

int R, S, hor, ver;
char grid[MAXN][MAXN];

map<pair<int, int>, int> hor_id, ver_id;
map<int, pair<int, int>> hor_coord, ver_coord;

vector<int> matchV, matchH;
vector<bool> bio, coverV, coverH;
vector<vector<int>> G;

inline void build_graph() {
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < S; ++j) {
      if (grid[i][j] == '0') continue;
      if (i + 1 < R && grid[i + 1][j] == '0') {
        ver_id[{i, j}] = ver;
        ver_coord[ver++] = {i + 1, j + 1};
      }
      if (j + 1 < S && grid[i][j + 1] == '0') {
        hor_id[{i, j}] = hor;
        hor_coord[hor++] = {i + 1, j + 1};
      }
    }
  }

  G.resize(ver_id.size());
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < S; ++j) {
      if (grid[i][j] == '1') continue;
      int _i = i - 1, _j = j - 1;
      while (grid[_i][j] == '0') --_i;
      while (grid[i][_j] == '0') --_j;
      G[ver_id[{_i, j}]].push_back(hor_id[{i, _j}]);
    }
  }
}

bool dfs(int node) {
  if (bio[node]) return false;
  bio[node] = true;
  for (int i : G[node]) {
    if (matchH[i] == -1 || dfs(matchH[i])) {
      matchH[i] = node;
      return true;
    }
  }
  return false;
}

int matching() {
  bio.resize(ver_id.size(), false);
  matchV.resize(ver_id.size(), -1);
  matchH.resize(hor_id.size(), -1);
  int ret = 0;
  for (int i = 0; i < (int)ver_id.size(); ++i) {
    fill(bio.begin(), bio.end(), false);
    ret += dfs(i);
  }
  return ret;
}

void alternate(int node) {
  coverV[node] = true;
  for (int i : G[node]) {
    if (coverH[i]) continue;
    assert(matchH[i] != -1);
    coverH[i] = true;
    alternate(matchH[i]);
  }
}

void vertex_cover() {
  coverV.resize(ver_id.size(), false);
  coverH.resize(hor_id.size(), false);
  for (int i = 0; i < (int)hor_id.size(); ++i) {
    if (matchH[i] != -1)
      matchV[matchH[i]] = i;
  }
  for (int i = 0; i < (int)ver_id.size(); ++i) {
    if (matchV[i] != -1) continue;
    alternate(i);
  }
}

void reconstruct() {
  for (int i = 0; i < (int)ver_id.size(); ++i) {
    const auto &coord = ver_coord[i];
    if (!coverV[i]) printf("%d %d DOLJE\n", coord.first, coord.second);
  }
  for (int i = 0; i < (int)hor_id.size(); ++i) {
    const auto &coord = hor_coord[i];
    if (coverH[i]) printf("%d %d DESNO\n", coord.first, coord.second);
  }
}

int main(void) {
  scanf("%d%d", &R, &S);
  for (int i = 0; i < R; ++i)
    scanf("%s", grid[i]);

  build_graph();
  printf("%d\n", matching());

  vertex_cover();
  reconstruct();

  return 0;
}
