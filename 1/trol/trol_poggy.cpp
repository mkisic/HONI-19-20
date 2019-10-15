#include <iostream>
#include <cstdio>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

int main() {
  int q;
  scanf("%d", &q);
  REP(i, q) {
    llint a, b;
    scanf("%lld %lld", &a, &b);
    llint rj = 0;
    while(a <= b && a % 9 != 0) {
      rj += a % 9;
      a++;
    }
    while(a <= b && b % 9 != 8) {
      if(!(b % 9)) rj += 9;
      else rj += b % 9;
      b--;
    }
    if(a < b) {
      rj += (b - a + 1) * 5;
    }
    printf("%lld\n", rj);
  }
  return 0;
}

