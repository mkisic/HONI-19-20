#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 3e5 + 10;
const int MAXH = 1e6 + 10;

int n, k;
int h[MAXN], cnt[MAXH];

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    cnt[h[i]]++;
  }

  for (int i = 0; i < n; ++i) {
    int ret = -1;
    for (int j = 1; j * j <= h[i]; ++j) {
      if (h[i] % j != 0) continue;
      ret += cnt[j];
      if (j * j != h[i]) ret += cnt[h[i] / j];
    }
    printf("%d ", ret);
  }
  printf("\n");

  return 0;
}
