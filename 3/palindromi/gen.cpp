#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);

  int n = atoi(argv[2]);
  int k = 2;
  if (argc >= 4) k = atoi(argv[3]);

  cout << n << endl;
  for (int i = 0; i < n; ++i)
    cout << (char)('a' + rand() % k);
  cout << endl;
  for (int i = 1; i < n; ++i) {
    int j = rand() % i;
    cout << i + 1 << " " << j + 1 << endl;
  }

  return 0;
}
