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

const lf EPS = 1e-12;

inline bool lt(const lf &a, const lf& b) { return b - a < EPS; }
inline bool eq(const lf &a, const lf& b) { return !lt(a, b) && !lt(b, a); }

typedef ll T;
struct pt {
  T x,y;
  pt() {}
  pt(pii t) {
    x = (T)t.fi;
    y = (T)t.sec;
  }
  pt(pll t) {
    x = (T)t.fi;
    y = (T)t.sec;
  }
  pt(T a, T b) {
    x = (T)a;
    y = (T)b;
  }
  pt operator-(pt p) {return pt(x-p.x, y-p.y);}

  friend bool operator < (pt a, pt b) {
    if (!eq(a.x, b.x)) return lt(a.x, b.x);
    return lt(a.y, b.y);
  }
};

bool operator==(pt a, pt b) {return eq(a.x, b.x) && eq(a.y, b.y);}
bool operator!=(pt a, pt b) {return !(a == b);}

lf cross(pt v, pt w) {return (lf)v.x*(lf)w.y - (lf)v.y*(lf)w.x;}
lf ccw(pt a, pt b, pt c) {return cross(b-a,c-a);}

const vector <string> cluster[3] = {
  {"1a", "1b", "1c", "1d", "2a", "2b", "2c", "2d", "2e", "2f", "2g"},
  {"3a", "3b", "3c", "3d", "3e", "3f", "4a", "4b", "4c", "4d"},
  {"4e", "5a", "5b", "5c", "5e", "5f", "5g", "5h", "5i"}};

const int HASH[] = {1, 0, 1};
const int Q[] = {2000, 100000, 100000};

const string IN_PREF = "svjetlost/svjetlost.in.";
const string OUT_PREF = "test/zvijezda.in.";

mt19937 rng(12345);

int Rand(int x) {
  return uniform_int_distribution<int>(0, x - 1)(rng);
}

mt19937_64 rngLL(12345);

ll RandLL(ll x = (1LL << 60)) {
  return uniform_int_distribution<ll>(0, x - 1)(rngLL);
}

int n;
vector <pii> poly;

bool get(int x, ll a, ll b) {
  return !lt(ccw(pt(poly[x]), pt(poly[(x + 1)%n]), pt(a, b)), 0);
}

bool pitaj(ll x, ll y) {
  int a = get(0, x, y);
  int b = get(n/2, x, y);
  if (a == b) return a;
  int lo = 0, hi = n/2-1, mid;
  while (lo != hi) {
    mid = (lo + hi + 1) / 2;
    if (get(mid, x, y) == a) lo = mid;
    else hi = mid - 1;
  }
  int L1 = 0, R1 = lo;
  lo = n/2;
  hi = n - 1;
  while (lo != hi) {
    mid = (lo + hi + 1) / 2;
    if (get(mid, x, y) == b) lo = mid;
    else hi = mid - 1;
  }
  int L2 = n/2, R2 = lo;
  int imam = 0;
  if (a == 1) {
    imam += R1 - L1 + 1;
    imam += n/2 - (R2 - L2 + 1);
  } else {
    imam += R2 - L2 + 1;
    imam += n/2 - (R1 - L1 + 1);
  }
  return imam >= n/2+1;
}

int CNT;

pii DA() {
  pll ret;
  int cnt = 0;
  do {
    cnt++;
    ret.fi = RandLL();
    ret.sec = RandLL();
    if (Rand(2)) ret.fi = -ret.fi;
    if (Rand(2)) ret.sec = -ret.sec;
  } while (!pitaj(ret.fi, ret.sec));
  CNT = max(CNT, cnt);
  return ret;
}

pii NE() {
  pll ret;
  int cnt = 0;
  do {
    cnt++;
    ret.fi = RandLL();
    ret.sec = RandLL();
    if (Rand(2)) ret.fi = -ret.fi;
    if (Rand(2)) ret.sec = -ret.sec;
  } while (!pitaj(ret.fi, ret.sec));
  CNT = max(CNT, cnt);
  return ret;
}

void napravi(int test, string OUT, string IN) {
  FILE *fin = fopen(IN.c_str(), "r");
  FILE *fout = fopen(OUT.c_str(), "w");

  poly.clear();
  fscanf(fin, "%d", &n);
  REP(i, n) {
    int x, y;
    fscanf(fin, "%d %d",&x,&y);
    poly.pb({x, y});
  }

  if (n % 2) {
    poly.erase(poly.begin() + Rand(n));
    n--;
  }

  CNT = 0;
  vector <pll> kveri_tocke;
  int q = Q[test] - Rand(5);

  int da = 0;
  REP(i, q) {
    int ok = Rand(2);
    pll tocka;
    if (ok) tocka = DA();
    else tocka = NE();
    if (HASH[test]) tocka.fi ^= da;
    if (HASH[test]) tocka.sec ^= da;
    da += ok;
    kveri_tocke.pb(tocka);
  }

  fprintf(fout, "%d\n", HASH[test]);
  fprintf(fout, "%d\n", n);
  REP(i, n) {
    fprintf(fout, "%d %d\n", poly[i].fi, poly[i].sec);
  }

  fprintf(fout, "%d\n",q);

  REP(i, q) {
    fprintf(fout, "%lld %lld\n", kveri_tocke[i].fi, kveri_tocke[i].sec);
  }

  TRACE("GOTOV" _ OUT _ n _ q _ da _ CNT);
  fclose(fin);
  fclose(fout);
}

int main() {
  REP(i, 3) {
    REP(j, (int)cluster[i].size()) napravi(i, OUT_PREF + char('1' + i) + char('a' + j), IN_PREF + cluster[i][j]);
  }
  return 0;
}

