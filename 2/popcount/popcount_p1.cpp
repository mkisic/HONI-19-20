#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

int n, k;

int main(void) {
  scanf("%d%d", &n, &k);
  printf("1\n");
  printf("A=(");
  for (int i = 0; i < n - 1; ++i)
    printf("((A&(1<<%d))>>%d)+(", i, i);
  printf("(A&(1<<%d))>>%d", n - 1, n - 1);
  for (int i = 0; i < n; ++i) printf(")");
  printf("\n");
  return 0;
}
