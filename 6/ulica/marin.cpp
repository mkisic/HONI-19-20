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

const int MAXN = 1000000;

int ima[3], moze[MAXN];
int n;

int main() {
  cin >> n;
  REP(i, n) {
    int x;
    cin >> x;
    ima[x % 2]++;
    moze[x] = 1;
  }
  int start = 2;
  if (ima[1] > ima[0]) start = 3;
  for (int i = start; i <= MAXN; i += 2) {
    if (!moze[i]) {
      cout << i << endl;
      return 0;
    }
  }
  return 0;
}

