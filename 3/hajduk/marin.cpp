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

int n, cnt, k;

int main() {
  cin >> n >> k;
  REP(i, n) {
    int x;
    cin >> x;
    if (x == 1) cnt++;
  }

  if (cnt * 2 >= n) puts("DA");
  else puts("NE");

  return 0;
}

