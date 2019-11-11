#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

int n;
vector<pair<int, int>> v;

bool fit(int a, int b) {
  return ((a == 1 || a == 3 || a == 5) && (b == 3 || b == 4 || b == 8)) ||
         ((a == 2 || a == 4 || a == 6) && (b == 1 || b == 2 || b == 7));
}

bool check() {
  if (v.front().second != 5 && v.front().second != 6) return false;
  if (v.back().second != 7 && v.back().second != 8) return false;
  for (int i = 1; i < (int) v.size(); ++i)
    if (!fit(v[i - 1].second, v[i].second))
      return false;
  return true;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, a;
    scanf("%d%d", &x, &a);
    v.emplace_back(a, x);
  }

  sort(v.begin(), v.end());
  do {
    if (check()) {
      for (const auto &p : v) printf("%d ", p.first);
      printf("\n");
      return 0;
    }
  } while (next_permutation(v.begin(), v.end()));

  printf("-1\n");
  return 0;
}
