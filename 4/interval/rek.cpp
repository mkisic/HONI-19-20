#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

const int MAXN = 101;
const int MAXM = MAXN * MAXN;

int n, L, R, K, p[MAXN];
int ansL[MAXN][MAXM], ansR[MAXN][MAXM];
int dp[MAXN][MAXN][MAXN * MAXN / 4 + 10];

int f(int a, int b, int c) {
  return c + b * MAXM + a * MAXM * MAXN;
}

int merge(int x) {
  int ret = 0;
  REP(k, K + 1) {
    int tmp = ansL[x][k];
    if (x + 1 <= R) tmp += ansR[x + 1][K - k];
    ret = max(ret, tmp);
  }
  return ret;
}

int rek(int i, int j, int k) {
  if (i >= L) return 0;
  if (j < L) return 0;
  if (dp[i][j][k] != -1) return dp[i][j][k];

  int ret = 0;
  ret = max(ret, rek(i + 1, j, k));
  ret = max(ret, rek(i, j - 1, k));
  if (k >= abs(i - j) && p[j] > p[i]) {
    ret = max(ret, rek(i + 1, j - 1, k - abs(i - j)) + p[j] - p[i]);
  }

  return dp[i][j][k] = ret;
}

int main() {
  cin >> n >> L >> R >> K;
  K = min(K, n * n / 4 + 2);
  L--; R--;
  REP(i, n) cin >> p[i];

  memset(dp, -1, sizeof dp);
  FOR(i, L, R + 1) {
    REP(k, K + 1) ansL[i][k] = rek(0, i, k);
  }

  int nR = n - L - 1;
  int nL = n - R - 1;
  swap(L, nL);
  swap(R, nR);
  reverse(p, p + n);
  memset(dp, -1, sizeof dp);
  FOR(i, L, R + 1) {
    REP(k, K + 1) ansR[n - i - 1][k] = rek(0, i, k);
  }

  swap(L, nL);
  swap(R, nR);
  reverse(p, p + n);

  int sol = ansR[L][K];
  FOR(i, L, R + 1) sol = max(sol, merge(i));
  int sum = 0;
  FOR(i, L, R + 1) sum += p[i];

  cout << sum - sol << endl;
  return 0;
}

