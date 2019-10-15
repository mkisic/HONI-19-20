#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl

#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1010;

const int smjer_x[4] = {1, -1, 0, 0};
const int smjer_y[4] = {0, 0, 1, -1};

const char tipovi[2] = {'T', 'B'};

int n, m;
int bio[MAXN][MAXN];

char mat[MAXN][MAXN];

vector<par> sljedeci;

void dfs(int x, int y, char tip) {
  if(mat[x][y] == '*') return;
  if(bio[x][y]) return;
  if(mat[x][y] != tip) {
    sljedeci.push_back(par(x, y));
    return;
  }
  bio[x][y] = 1;
  REP(i, 4) {
    int kamo_x = x + smjer_x[i];
    int kamo_y = y + smjer_y[i];
    if(kamo_x < 0 || kamo_x >= n) continue;
    if(kamo_y < 0 || kamo_y >= m) continue;
    dfs(kamo_x, kamo_y, tip);
  }
}

int main() {
  scanf("%d %d", &n, &m);
  REP(i, n)
    scanf("%s", &mat[i]);
  int rj = 0;
  int vrsta = 0;
  if(mat[n - 1][m - 1] == 'B') vrsta = 1;
  sljedeci.push_back(par(n - 1, m - 1));
  while(sljedeci.size() > 0) {
    vector<par> v = sljedeci;
    sljedeci.clear();
    for(const auto &x : v)
      dfs(x.X, x.Y, tipovi[vrsta]);
    vrsta = !vrsta;
    rj++;
  }
  printf("%d\n", rj);
  return 0;
}

