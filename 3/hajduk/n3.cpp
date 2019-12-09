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

int n, k;
int a, b, c;
int main() {
  cin >> n >> k;
  cin >> a >> b;
  if (n == 3) cin >> c;
  if (a == 1 && (b == 1 || c == 1)) cout << "DA" << endl;
  else if (b == 1 && (a == 1 || c == 1)) cout << "DA" << endl;
  else if (c == 1 && (a == 1 || b == 1)) cout << "DA" << endl;
  else cout << "NE" << endl;
  return 0;
}

