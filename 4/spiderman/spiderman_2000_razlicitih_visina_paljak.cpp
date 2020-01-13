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
int h[MAXN], sol[MAXH];

map<int, int> m;

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    m[h[i]]++;
  }

  for (const auto &p : m) {
    for (const auto &q : m) {
      if (p.first == q.first) continue;
      if (p.first % q.first == k) sol[p.first] += q.second;
    }
  }

  for (int i = 0; i < n; ++i) printf("%d ", sol[h[i]]);
  printf("\n");

  return 0;
}
