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

const int MAXN = 501;
const int MOD = 1e9 + 7;

int add(int a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
  return a;
}

int mul(int a, int b) {
  return (ll)a * b % MOD;
}

int n, dp[2][MAXN][MAXN];
int povrh[MAXN][MAXN];

int f(int a, int b) {
  if (a < b) return 1;
  if (b == 1) return a;
  if (b == a || b == 0) return 1;
  if (povrh[a][b] != -1) return povrh[a][b];
  int ret = f(a - 1, b - 1);
  ret = add(ret, f(a - 1, b));
  return povrh[a][b] = ret;
}

int rek(int ok, int a, int b) {
  if (b == n + 1) {
    if (a != 0) return 0;
    return ok;
  }
  if (a == 0) return ok;
  if (dp[ok][a][b] != -1) return dp[ok][a][b];
  int ret = 0;
  REP(i, a + 1) {
    ret = add(ret, mul(f(a, i), rek(ok | (b == i), a - i, b + 1)));
  }
  return dp[ok][a][b] = ret;
}

int main() {
  cin >> n;
  memset(dp, -1, sizeof dp);
  memset(povrh, -1, sizeof povrh);
  cout << rek(0, n, 1) << endl;
  return 0;
}

