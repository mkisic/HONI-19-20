#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 2010;

int n, k;
int h[MAXN];

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d", &h[i]);

  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
      if (j == i) continue;
      if (h[i] % h[j] == k) ++cnt;
    }
    printf("%d ", cnt);
  }
  printf("\n");

  return 0;
}
