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

const int MAXN = 10;

int bio[MAXN];

bool prime(ll x) {
  if (x < 2) return 0;
  for (ll i = 2; i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}

ll a, b;

int main() {
  cin >> a >> b;
  if (prime(max(a - b, b - a))) {
    cout << 2 << endl << a << ' ' << b << endl;
    return 0;
  }

  FOR(i, 2, 1001) {
    if (prime(i) && prime(max(a - i, i - a)) && prime(max(i - b, b - i))) {
      cout << 3 << endl << a << ' ' << i << ' ' << b << endl;
      return 0;
    }
  }

  puts("-1");
  return 0;
}
