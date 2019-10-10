#include <cstdio>

using namespace std;

int q;

int main(void) {
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int sol = 0;
    for (int i = l; i <= r; ++i) sol += i;
    printf("%d\n", sol);
  }
  return 0;
}
