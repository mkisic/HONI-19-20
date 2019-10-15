#include <bits/stdc++.h>
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

const int MAXN = 1010;

int bio[MAXN];

bool prosti(ll x) {
  if (x < 2) return 0;
  for (ll i = 2; i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}

int a, b;

int tko[MAXN];

int main() {
  cin >> a >> b;

  tko[a] = -1;
  queue <int> q;
  q.push(a);
  bio[a] = 1;

  while (!q.empty()) {
    int cvor = q.front(); q.pop();
    if (cvor == b) break;

    FOR(i, 2, 1001) {
      if (!bio[i] && prosti(i) && prosti(max(i - cvor, cvor - i))) {
        bio[i] = 1;
        tko[i] = cvor;
        q.push(i);
      }
    }
  }

  if (!bio[b]) {
    puts("-1");
    return 0;
  }

  vector <int> ans;
  int cvor = b;
  while (cvor != -1) {
    ans.pb(cvor);
    cvor = tko[cvor];
  }

  reverse(all(ans));
  printf("%d\n",ans.size());
  for (auto x : ans) printf("%d ",x);
  puts("");

  return 0;
}
