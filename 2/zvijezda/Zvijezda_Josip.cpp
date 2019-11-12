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
#define TRACE(x) cerr << #x << "  " << x << endl
template<typename T1, typename T2>inline void minaj(T1 &x, T2 y) { x = (x > y ? y: x);}
template<typename T1, typename T2>inline void maxaj(T1 &x, T2 y) { x = (x < y ? y: x);}

typedef double lf;
typedef long long ll;
typedef pair<lf, lf> plf;

const int mod = 1e9 + 7;
int add(int x, int y) {x += y; if(x >= mod) return x - mod; return x;}
int sub(int x, int y) {x -= y; if(x < 0) return x + mod; return x;}
int mul(int x, int y) {return (ll) x * y % mod;}

const lf eps = 1e-9;
const int MAXN = 1e6 + 5;

lf ccw(plf A, plf B, plf C) {
  return A.fi * (B.se - C.se) +
         B.fi * (C.se - A.se) +
         C.fi * (A.se - B.se);
}

int n;
plf P;

lf a[MAXN], b[MAXN];
plf p[MAXN];

int sgn(lf x) {
  if(x < -eps) return -1;
  if(x > +eps) return +1;
  return 0;
}

int duz(int i, plf A) {
  i = (i + n) % n;
  int s = sgn(ccw(p[i], p[i + 1], A));
  if(s == 0 || s == sgn(ccw(p[i], p[i + 1], P))) return 1;
  return 0;
}

bool solve(lf x, lf y) {
  int v1 = duz(0, {x, y});
  int v2 = duz(n / 2, {x, y});
  if(v1 == v2) {
    if(v1 == 1) return true;
    return false;
  }
  int pl = n / 2;
  if(v1) {
    pl = 0;
  }

  int ret = 0;

  int lo = 0, hi = n / 2 - 1;
  while(lo < hi) {
    int mi = (lo + hi + 1) >> 1;
    if(duz(mi + pl, {x, y})) {
      lo = mi;
    }
    else {
      hi = mi - 1;
    }
  }
  ret += lo;
  lo = 0, hi = n / 2 - 1;
  while(lo < hi) {
    int mi = (lo + hi + 1) >> 1;
    if(duz(-mi + pl, {x, y})) {
      lo = mi;
    }
    else {
      hi = mi - 1;
    }
  }
  ret += lo + 1;
  if(ret > n / 2) return true;
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int t; cin >> t;

  lf A = 0, B = 0;
  cin >> n;
  REP(i, n) {
    cin >> a[i] >> b[i];
    A += a[i];
    B += b[i];
    p[i] = {a[i], b[i]};
  }
  p[n] = p[0];
  A /= n;
  B /= n;
  P = {A, B};

  ll cnt = 0;
  int q; cin >> q;
  REP(i, q) {
    ll x, y; cin >> x >> y;
    x ^= cnt * t;
    y ^= cnt * t;

    if(solve((lf) x, (lf) y)) {
      cout << "DA\n";
      cnt ++;
    }
    else {
      cout << "NE\n";
    }
  }
}