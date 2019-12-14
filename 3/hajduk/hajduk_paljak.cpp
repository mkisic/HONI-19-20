#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

int n, k, a, b;

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    a += x == 1;
    b += x != 1;
  }
  if (a >= b) printf("DA\n"); else printf("NE\n");
  return 0;
}
