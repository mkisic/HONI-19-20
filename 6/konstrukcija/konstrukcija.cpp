#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

struct graf {
  int n;
  vector<par> bridovi;
  vector<int> zadnji_sloj;
  graf(int _n, vector<par> _bridovi) {
    n = _n;
    bridovi = _bridovi;
  }
  graf() {
    n = 1;
    zadnji_sloj.push_back(1);
  }

  llint puta_minus_dva(llint pref) {
    vector<int> novi = {n + 1, n + 2, n + 3};
    for(auto x : zadnji_sloj)
      for(auto y : novi)
        bridovi.push_back(par(x, y));
    zadnji_sloj = novi;
    n = n + 3;
    return -2 * pref;
  }

  llint oduzmi_jedan(llint pref) {
    bridovi.push_back(par(1, n + 1));
    zadnji_sloj.push_back(n + 1);
    n = n + 1;
    return pref - 1;
  }

  llint dodaj_jedan(llint pref) {
    vector<int> novi = {n + 1, n + 2};
    for(auto x : zadnji_sloj)
      for(auto y : novi)
        bridovi.push_back(par(x, y));
    bridovi.push_back(par(1, n + 3));
    novi.push_back(n + 3);
    zadnji_sloj = novi;
    n = n + 3;
    return -pref - 1; // primjeti: ovo zapravo nije "dodaj 1",
  }                   // ali je u smislu apsolutne vrijenosti

  void zavrsi_isti() {
    vector<int> novi = {n + 1, n + 2};
    for(auto x : zadnji_sloj)
      for(auto y : novi)
        bridovi.push_back(par(x, y));
    zadnji_sloj = novi;
    for(auto x : zadnji_sloj)
      bridovi.push_back(par(x, n + 3));
    n = n + 3;
  }

  void zavrsi_minus() {
    for(auto x : zadnji_sloj)
      bridovi.push_back(par(x, n + 1));
    n = n + 1;
  }

  void ispis() {
    printf("%d %d\n", n, (int) bridovi.size());
    for(auto p : bridovi)
      printf("%d %d\n", p.X, p.Y);
  }

};

vector<int> odredi_binarni_zapis(llint t) {
  vector<int> ret;
  while(t > 0) {
    if(t & 1) ret.push_back(1);
    else ret.push_back(0);
    t /= 2;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

graf rijesi(llint t) {
  if(t == 0) {
    graf g(3, {par(1, 2), par(2, 3)});
    return g;
  }
  graf g;
  vector<int> binarno = odredi_binarni_zapis(abs(t)); 
  llint pref = 1;
  FOR(i, 1, (int) binarno.size()) {
    pref = g.puta_minus_dva(pref);
    if(binarno[i]) {
      if(pref < 0)
        pref = g.oduzmi_jedan(pref);
      else
        pref = g.dodaj_jedan(pref);
    }
  }
  assert(abs(t) == abs(pref));
  if(pref == t) g.zavrsi_isti();
  else g.zavrsi_minus();
  return g;
}

void pozovi(llint t) {
  graf g = rijesi(t);
  g.ispis();
}

int main() {
  llint t;
  cin >> t;
  pozovi(t);
  return 0;
}

