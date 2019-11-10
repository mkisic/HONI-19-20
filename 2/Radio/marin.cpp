#include <bits/stdc++.h>
using namespace std;

int n;
long long x;

int main() {
  scanf("%d %lld",&n,&x);
  for (int i = 0; i < n; i++) {
    long long a, b;
    scanf("%lld %lld",&a,&b);
    x += b - a;
  }
  printf("%lld\n",x);
  return 0;
}
