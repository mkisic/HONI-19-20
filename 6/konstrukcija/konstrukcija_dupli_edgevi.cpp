#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 1e6 + 10;

vector<par> bridovi;

int main() {
  llint n;
  cin >> n;
  TRACE(n);
  if(abs(n) > 1e6) return 0;
  int num = 1;
  if(n < 0) {
    n *= -1;
    FOR(i, 2, n + 3) {
      bridovi.push_back(par(1, i));
    }
    FOR(i, 2, n + 3) {
      bridovi.push_back(par(i, n + 3));
      bridovi.push_back(par(i, n + 4));
    }
    bridovi.push_back(par(n + 3, n + 5));
    bridovi.push_back(par(n + 4, n + 5));
    num = n + 5;
  }
  else if(n > 0) {
    FOR(i, 2, n + 3) {
      bridovi.push_back(par(1, i));
      bridovi.push_back(par(i, n + 3));
    }
    bridovi.push_back(par(n + 2, n + 3));
    num = n + 3;
  }
  cout << num << " " << bridovi.size() << endl;
  cerr << ":::::::::::::: " << num << ", " << bridovi.size() << " START" << endl;
  for(auto p : bridovi) {
    cout << p.X << " " << p.Y << endl;
    //if(bridovi.size() < 30) cerr << ":::::::::::::: " << p.X << ", " << p.Y << endl;
  }
  return 0;
}

