#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

int n;

int main(void) {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int d;
    string m;
    cin >> d >> m;
    if (d % 2 == 0)
      cout << "BROKULA\n";
    else
      cout << "MRKVA\n";
  }
  return 0;
}
