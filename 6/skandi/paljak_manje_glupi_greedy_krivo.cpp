#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 505;

struct Question {
  int r, s, dr, ds, len;
  friend bool operator<(const Question &A, const Question &B) {
    return A.len > B.len;
  }
};

bool bio[MAXN][MAXN];

int R, S;
char grid[MAXN][MAXN];

vector<Question> Q;
vector<tuple<int, int, int>> sol;

inline bool check_bio() {
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < S; ++j)
      if (grid[i][j] == '0' && !bio[i][j])
        return false;
  return true;
}

Question get_question() {
  Question ret = {0, 0, 0, 0, -1};
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < S; ++j) {
      if (grid[i][j] == '1') continue;
      int _i = i, _j = j;
      int s1 = 0, s2 = 0;
      while (grid[_i][j] == '0') s1 += !bio[_i--][j];
      while (grid[i][_j] == '0') s2 += !bio[i][_j--];
      Question q1 = {_i, j, 1, 0, s1};
      Question q2 = {i, _j, 0, 1, s2};
      if (q1 < ret) ret = q1;
      if (q2 < ret) ret = q2;
    }
  }
  return ret;
}

int main(void) {
  scanf("%d%d", &R, &S);
  for (int i = 0; i < R; ++i)
    scanf("%s", grid[i]);

  while (!check_bio()) {
    const auto &q = get_question();
    //TRACE(q.r _ q.s _ q.dr _ q.ds _ q.len);
    int r = q.r + q.dr, s = q.s + q.ds;
    bool flag = false;
    while (r < R && s < S && grid[r][s] == '0' && !flag) {
      flag |= !bio[r][s];
      r += q.dr;
      s += q.ds;
    }
    if (!flag) continue;
    r = q.r + q.dr; s = q.s + q.ds;
    while (r < R && s < S && grid[r][s] == '0') {
      bio[r][s] = true;
      r += q.dr;
      s += q.ds;
    }
    sol.emplace_back(q.r, q.s, q.dr == 1);
  }

  printf("%d\n", (int) sol.size());
  for (const auto &t : sol) {
    if (get<2>(t) == 1)
      printf("%d %d DOLJE\n", get<0>(t) + 1, get<1>(t) + 1);
    else
      printf("%d %d DESNO\n", get<0>(t) + 1, get<1>(t) + 1);
  }

  return 0;
}
