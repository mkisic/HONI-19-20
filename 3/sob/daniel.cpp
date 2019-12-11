#include <bits/stdc++.h>
using namespace std;
int N, K;

void output(int a, int b) {
  cout << a << " " << b << endl;
}

void solve() {
  for (int i = K - 1; i >= 0; i--) {
    int z = 0, len = 0;
    for (z = N - i - 1; (i & z) != i; z++) len++;
    output(i, z);
    int j = i;
    for (int r = z - 1; r >= N - i - 1; r--) {
      output(--j, r);
    }
    i -= len;
  }
}

void load() {
  cin >> N >> K;
}

int main() {
  load();
  solve();
  return 0;
}

