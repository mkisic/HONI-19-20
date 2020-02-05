#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

int a, b;

llint n;

set<llint> A, B, AUB;

void read(int *n, set<llint> &S) {
  scanf("%d", n);
  for (int i = 0; i < *n; ++i) {
    llint x;
    scanf("%lld", &x);
    S.insert(x);
    AUB.insert(x);
  }
}

int main(void) {
  scanf("%lld", &n);
  read(&a, A);
  read(&b, B);
  int ab = (int) A.size() + (int) B.size() - (int) AUB.size();
  printf("%d\n%d\n", (int) A.size() - ab, (int) B.size() - ab);
  return 0;
}
