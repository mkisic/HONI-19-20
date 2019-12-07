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

const int MAXN = 30;

int n, p[MAXN];

int main() {
  cin >> n;
  REP(i, n) cin >> p[i];
  sort(p, p + n);
  if (n > 25 || n == 1) {
    puts("-1");
    return 0;
  }

  vector <int> v[2];
  REP(mask, (1 << n)) {
    REP(j, 2) v[j].clear();
    REP(i, n) {
      if (mask & (1 << i)) v[1].pb(p[i]);
      else v[0].pb(p[i]);
    }

    bool ok = 1;
    REP(j, 2) FOR(i, 1, (int)v[j].size()) if (v[j][i] - v[j][i - 1] != v[j][1] - v[j][0]) ok = 0;
    if (ok) {
      printf("%d %d\n",(int)v[0].size(),(int)v[1].size());
      REP(i, 2) {
        for (auto x : v[i]) printf("%d ", x);
        puts("");
      }
      return 0;
    }
  }
  return 0;
}

