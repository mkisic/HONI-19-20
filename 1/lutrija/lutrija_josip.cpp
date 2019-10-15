#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<
#define pb push_back
#define fi first
#define se second
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
template<typename T1, typename T2>inline void minaj(T1 &x, T2 y) { x = (x > y ? y: x);}
template<typename T1, typename T2>inline void maxaj(T1 &x, T2 y) { x = (x < y ? y: x);}

typedef double lf;
typedef long long ll;
typedef pair<int, int> pii;

const int mod = 1e9 + 7;
int add(int x, int y) {x += y; if(x >= mod) return x - mod; return x;}
int sub(int x, int y) {x -= y; if(x < 0) return x + mod; return x;}
int mul(int x, int y) {return (ll) x * y % mod;}

bool prost(ll a) {
  a = abs(a);
  if(a < 2) return false;
  for(ll x = 2; x * x <= a; ++x) {
    if(a % x == 0) return false;
  }
  return true;
}

vector<ll> v;

void fail() {
  cout << -1 << endl;
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  ll a, b; cin >> a >> b;
  if(prost(b - a)) {
    cout << 2 << endl;
    cout << a _ b << endl;
    return 0;
  }
  else if(abs(b - a) == 4 && min(a, b) == 3) {
    cout << 3 << endl;
    cout << a _ a + (b - a) / 2 _ b << endl;
    return 0;
  }
  else {
    v.pb(a);
    if(a != 2) {
      if(prost(a - 2)) {
        v.pb(2);
      }
      else if(prost(a + 2)) {
        v.pb(a + 2);
        v.pb(2);
      }
      else {
        fail();
      }
    }
    if(b != 2) {
      if(prost(b - 2)) {
        v.pb(b);
      }
      else if(prost(b + 2)) {
        v.pb(b + 2);
        v.pb(b);
      }
      else {
        fail();
      }
    }
  }
  cout << v.size() << endl;
  for(auto x: v) cout << x << " ";
  cout << endl;
}
