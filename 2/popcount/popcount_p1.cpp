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
  printf("%d\n", n - 1);
  for (int i = 1; i < n; ++i)
    printf("A=((A&(((1<<%d)-1)-(1<<%d)))+((A&(1<<%d))>>%d))\n", n, i, i, i);
  return 0;
}
