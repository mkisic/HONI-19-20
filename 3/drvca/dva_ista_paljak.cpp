#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1e5 + 10;

int n;
int h[MAXN];

void solve(int a0, int a1) {
  vector<int> a = {a0, a1}, b;
  for (int i = 0; i < n; ++i) {
    if (h[i] - a.back() == a1 - a0)
      a.emplace_back(h[i]);
    if (a.size() == n / 2) break;
  }
  int ptr = 0;
  for (int i = 0; i < n; ++i) {
    if (ptr < a.size() && h[i] == a[ptr]) {
      ++ptr;
      continue;
    }
    b.emplace_back(h[i]);
  }

  if (b.size() >= 2) {
    for (int i = 1; i < b.size(); ++i)
      if (b[i] - b[i - 1] != b[1] - b[0])
        return;
  }

  if (a.size() != n / 2 || b.size() != n / 2) return;

  printf("%d\n", n / 2);
  for (int x : a) printf("%d ", x);
  printf("\n");
  printf("%d\n", n / 2);
  for (int x : b) printf("%d ", x);
  printf("\n");
  exit(0);
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &h[i]);

  if (n % 2 != 0) {
    printf("-1\n");
    return 0;
  }

  sort(h, h + n);

  if (h[0] == h[n - 1]) {
    for (int j = 0; j < 2; ++j) {
      printf("%d\n", n / 2);
      for (int i = 0; i < n / 2; ++i)
        printf("%d ", h[0]);
      printf("\n");
    }
    return 0;
  }

  solve(h[0], h[1]);
  if (n >= 3) solve(h[0], h[2]);
  if (n >= 3) solve(h[1], h[2]);

  printf("-1\n");
  return 0;
}
