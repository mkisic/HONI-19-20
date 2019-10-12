#include <bits/stdc++.h>
using namespace std;

int n;
long long a, b, rj;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    long long mnozi = 1;
    long long x = b;
    while (x) {
      mnozi *= 10;
      x /= 10;
    }
    rj += a * mnozi + b;
  }
  cout << rj << endl;
  return 0;
}
