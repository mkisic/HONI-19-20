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

const int MAXN = 55;
const int MAXK = 1505;
const int MAXM = MAXN * MAXK;

const int MOD = 1e9 + 7;

int add(int a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
  return a;
}

int mul(int a, int b) {
  return (ll)a * b % MOD;
}

int n, k;
int cnt[MAXM], dp[MAXM];

unordered_map <string, int> ime;
int IME;

vector <int> v[MAXM];
string s;

int rek(int cvor) {
  if (dp[cvor] != -1) return dp[cvor];
  int ret = 0;
  sort(all(v[cvor]));
  REP(i, (int)v[cvor].size()) {
    int ncvor = v[cvor][i];
    if (i && v[cvor][i - 1] == ncvor) continue;
    ret = add(ret, mul(cnt[cvor], rek(ncvor)));
  }
  return dp[cvor] = ret;
}

int main() {
  scanf("%d %d",&n,&k);
  memset(dp, -1, sizeof dp);
  REP(i, n) {
    REP(j, k) {
      cin >> s;
      if (!ime.count(s)) {
        ime[s] = ++IME;
      }
      int cvor = ime[s];
      cnt[cvor]++;
      if (i == n - 1) dp[cvor] = cnt[cvor];

      if (i) {
        REP(start, 2) {
          string t = s.substr(start, i);
          if (ime.count(t)) {
            v[ime[t]].pb(cvor);
          }
        }
      } else {
        if (cnt[cvor] == 1) {
          v[n * k + 1].pb(cvor);
        }
      }
    }
  }

  cnt[n * k + 1] = 1;
  printf("%d\n",rek(n * k + 1));
  return 0;
}

