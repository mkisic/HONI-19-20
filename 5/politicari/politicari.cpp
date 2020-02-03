#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 505;

int n;
int mat[MAXN][MAXN], bio[MAXN][MAXN], guest[MAXN * MAXN];

llint k;

int main(void) {
  scanf("%d%lld", &n, &k);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &mat[i][j]);
      --mat[i][j];
    }
  }

  int prev = 0, curr = 1;
  guest[1] = 0;
  guest[2] = 1;
  bio[prev][curr] = 2;
  for (int i = 3; (llint) i <= k; ++i) {
    int nxt = mat[curr][prev];
    prev = curr;
    curr = nxt;
    if (bio[prev][curr] == 0) {
      bio[prev][curr] = i;
      guest[i] = curr;
      continue;
    }
    int j = bio[prev][curr];
    int cycle = i - j;
    int ret = j + ((k - j) % cycle);
    printf("%d\n", guest[ret] + 1);
    return 0;
  }

  printf("%d\n", guest[k] + 1);
  return 0;
}
