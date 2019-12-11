#include <bits/stdc++.h>
using namespace std;
int N, M;

void output(int a, int b) {
  cout << a << " " << b << endl;
}

void solve() {
  for (int i = N - 1; i >= 0; i--) {
    int z = 0, len = 0;
    for (z = N + M - i - 1; (i & z) != i; z++) len++;
    output(i, z);
    int j = i;
    for (int r = z - 1; r >= N + M - i - 1; r--) {
      output(--j, r);
    }
    i -= len;
  }
}

void load() {
  cin >> N >> M;
}

int main() {
  load();
  solve();
  return 0;
}

