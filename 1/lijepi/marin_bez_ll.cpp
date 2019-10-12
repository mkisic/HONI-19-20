#include <bits/stdc++.h>
using namespace std;

int n;
int a, b, rj;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    int mnozi = 1;
    int x = b;
    while (x) {
      mnozi *= 10;
      x /= 10;
    }
    rj += a * mnozi + b;
  }
  cout << rj << endl;
  return 0;
}
