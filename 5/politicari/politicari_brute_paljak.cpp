#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 505;

int n, k;
int mat[MAXN][MAXN];

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%d", &mat[i][j]);

  if (k < 3) {
    printf("%d\n", k);
    return 0;
  }

  int prev = 0;
  int curr = 1;

  for (int i = 0; i < k - 2; ++i) {
    int nxt = mat[curr][prev] - 1;
    prev = curr;
    curr = nxt;
  }

  printf("%d\n", curr + 1);
  return 0;
}
