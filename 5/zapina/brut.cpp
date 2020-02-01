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

int n, ans;
int cnt[10];

int check(int mask) {
  memset(cnt, 0, sizeof cnt);
  REP(i, n) {
    cnt[(mask % n) + 1]++;
    mask /= n;
  }
  FOR(i, 1, n + 1) if (cnt[i] == i) return 1;
  return 0;
}

void ispis(int x) {
  REP(i, n) {
    fprintf(stderr, "%d",(x % n)+1);
    x /= n;
  }
}

int main() {
  cin >> n;
  int N = 1;
  REP(i, n) N *= n;
  REP(mask, N) {
    ans += check(mask);
  }
  cout << ans << endl;
  return 0;
}

