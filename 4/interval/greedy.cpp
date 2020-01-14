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

const int MAXN = 110;

int n, p[MAXN], L, R, K;
int bio[MAXN];

int main() {
  cin >> n >> L >> R >> K;
  L--; R--;
  REP(i, n) cin >> p[i];
  
  bool jesam = 1;
  while (K > 0 && jesam) {
    jesam = 0;
    int a = -1, b = -1;
    int raz = 0;
    REP(i, n) {
      if (i >= L && i <= R) continue;
      if (bio[i]) continue;
      FOR(j, L, R + 1) {
        if (bio[j]) continue;
        if (abs(i - j) > K) continue;
        if (p[j] - p[i] > raz) {
          raz = p[j] - p[i];
          a = i;
          b = j;
        }
      }
    }
    if (a == -1) continue;
    K -= abs(a - b);
    jesam = 1;
    swap(p[a], p[b]);
    bio[a] = bio[b] = 1;
  }
  
  int sum = 0;
  FOR(i, L, R + 1) sum += p[i];
  cout << sum << endl;
  return 0;
}

