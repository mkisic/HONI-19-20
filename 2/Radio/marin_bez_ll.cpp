#include <bits/stdc++.h>
using namespace std;

int n;
int x;

int main() {
  scanf("%d %d",&n,&x);
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d %d",&a,&b);
    x += b - a;
  }
  printf("%d\n",x);
  return 0;
}
