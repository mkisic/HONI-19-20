#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

int main() {
  srand(time(NULL) * getpid());
  int n = rand()%10 + 5;
  int l = rand()%n;
  int r = rand()%n;
  if (l > r) swap(l, r);
  int k = rand()%20;
  printf("%d %d %d %d\n",n,l+1,r+1,k);
  REP(i, n) printf("%d ",rand()%20);
  puts("");
  return 0;
}

