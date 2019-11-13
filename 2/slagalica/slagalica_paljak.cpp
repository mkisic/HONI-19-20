#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 10;

bool l, r;
bool ll[4] = {1, 0, 1, 0};

int n, fst, lst;
int cnt[4];

priority_queue<int, vector<int>, greater<int>> puzzle[4];

bool ok(bool left, bool right) {
  if (abs(cnt[0] - cnt[3]) > 1) return false;
  if (left != right && abs(cnt[0] - cnt[3]) == 1) return false;
  if (left == right && left && cnt[3] <= cnt[0]) return false;
  if (left == right && !left && cnt[0] <= cnt[3]) return false;
  if (cnt[0] + cnt[3] == 0 && left && cnt[1] > 0) return false;
  if (cnt[0] + cnt[3] == 0 && !left && cnt[2] > 0) return false;
  return true;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, a;
    scanf("%d%d", &x, &a); --x;
    if (x < 4) puzzle[x].push(a), ++cnt[x];
    l |= x == 4;
    r |= x == 6;
    fst += a * (x == 4 || x == 5);
    lst += a * (x == 6 || x == 7);
  }

  if (!ok(l, r)) {
    printf("-1\n");
    return 0;
  }

  printf("%d ", fst);

  for (int i = 0; i < n - 2; ++i) {
    int pivot = -1, best = MOD;
    for (int j = 0; j < 4; ++j) {
      if (puzzle[j].empty()) continue;
      --cnt[j];
      if (ok(ll[j], r) && puzzle[j].top() < best)
        pivot = j, best = puzzle[j].top();
      ++cnt[j];
    }

    printf("%d ", best);
    puzzle[pivot].pop();
    --cnt[pivot]; l = ll[pivot];
  }

  printf("%d\n", lst);
  return 0;
}
