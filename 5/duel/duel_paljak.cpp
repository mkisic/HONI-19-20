#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

int a, b;

llint n;

set<llint> A, B;

void read(int *n, set<llint> &S) {
  scanf("%d", n);
  for (int i = 0; i < *n; ++i) {
    llint x;
    scanf("%lld", &x);
    S.insert(x);
  }
}

int diff(const set<llint> &A, const set<llint> &B) {
  int ret = 0;
  for (const llint x : A)
    ret += B.find(x) == B.end();
  return ret;
}

int main(void) {
  scanf("%lld", &n);
  read(&a, A);
  read(&b, B);
  printf("%d\n%d\n", diff(A, B), diff(B, A));
  return 0;
}
