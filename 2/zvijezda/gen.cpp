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


const vector <string> cluster[3] = {
  {"1a", "1b", "1c", "1d", "2a", "2b", "2c", "2d", "2e", "2f", "2g"},
  {"3a", "3b", "3c", "3d", "3e", "3f", "4a", "4b", "4c", "4d"},
  {"4e", "5a", "5b", "5c", "5e", "5f", "5g", "5h", "5i"}};

const int HASH[] = {0, 0, 1};
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

lf ccw(pll a, pll b, pll c) {
  return (lf)a.fi * (b.sec - c.sec) +
         (lf)b.fi * (c.sec - a.sec) +
         (lf)c.fi * (a.sec - b.sec);
}

bool get(int i, ll x, ll y) {
  return ccw(poly[i], poly[(i+1)%n], {x, y}) >= 0;
}

int mjeri(int l, int r, ll x, ll y) {
  int lo = l, hi = r, mid;
  while (lo != hi) {
    mid = (lo + hi + 1) / 2;
    if (get(mid, x, y) == get(l, x, y)) lo = mid;
    else hi = mid - 1;
  }
  int ret = lo - l + 1;
  if (!get(l, x, y)) ret = n/2 - ret;
  return ret;
}

bool pitaj(ll x, ll y) {
  int a = get(0, x, y);
  int b = get(n/2, x, y);
  if (a == b) return a;
  return mjeri(0, n/2 - 1, x, y) + mjeri(n/2, n - 1, x, y) > n / 2;
}

int CNT;

pll get_point(int pozitiv, ll da, int sad) {
  pll ret;
  int cnt = 0;
  do {
    cnt++;
    ret.fi = RandLL();
    ret.sec = RandLL();
    if (Rand(2)) ret.fi = -ret.fi;
    if (Rand(2)) ret.sec = -ret.sec;
  } while (pitaj(ret.fi, ret.sec) != pozitiv || sad * (pitaj(ret.fi ^ da, ret.sec ^ da) == pozitiv));
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
  int moze = 3;
  REP(i, q) {
    int ok = Rand(2);
    ll ksor = 0;
    ksor = da;
    if (i > 10000 && moze && Rand(1000) == 1) {
      ksor = da;
      moze--;
    }
    else ksor = 0;
    ksor *= HASH[test];
    pll tocka = get_point(ok, (ll)ksor * ksor * ksor, ksor > 0);
    if (HASH[test]) tocka.fi ^= ((ll)da * da * da);
    if (HASH[test]) tocka.sec ^= ((ll)da * da * da);
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

