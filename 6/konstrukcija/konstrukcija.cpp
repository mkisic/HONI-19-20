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

  int dobar_format() {
    for(auto p : bridovi) {
      if(p.X < 1 || p.X > n) return 0;
      if(p.Y < 1 || p.Y > n) return 0;
      if(p.X == p.Y) return 0;
    }
    return 1;
  }

  int dfs(int cvor, vector<int> &boja) {
    if(boja[cvor] == 1) return 0;
    if(boja[cvor] == 2) return 1;
    boja[cvor] = 1;
    int ret = 1;
    for(auto p : bridovi)
      if(p.X == cvor)
        ret &= dfs(p.Y, boja);
    boja[cvor] = 2;
    return ret;
  }

  int ima_ciklusa() {
    vector<int> boja(n + 1);
    FOR(i, 1, n + 1)
      if(!boja[i])
        if(!dfs(i, boja))
          return 1;
    return 0;
  }

  void topoloski(int cvor, vector<int> &bio, vector<int> &poredak) {
    if(bio[cvor]) return;
    bio[cvor] = 1;
    for(auto p : bridovi)
      if(p.Y == cvor)
        topoloski(p.X, bio, poredak);
    poredak.push_back(cvor);
  }

  void odredi_pretke(int cvor, vector<int> &imam, vector<int> &v) {
    if(imam[cvor]) return;
    imam[cvor] = 1;
    v.push_back(cvor);
    for(auto p : bridovi)
      if(p.Y == cvor)
        odredi_pretke(p.X, imam, v);
  }

  llint odredi_funkciju() {
    vector<int> bio(n + 1);
    vector<int> poredak;
    FOR(i, 1, n + 1)
      if(!bio[i])
        topoloski(i, bio, poredak);
    vector<llint> dp(n + 1);
    vector<vector<int> > preci(n + 1);
    FOR(i, 1, n + 1) {
      vector<int> imam(n + 1);
      odredi_pretke(i, imam, preci[i]);
    }
    for(auto x : poredak) {
      if(x == 1)
        dp[x] = 1;
      else {
        llint suma_predaka = 0;
        for(auto v : preci[x])
          suma_predaka += dp[v];
        dp[x] = -1 * suma_predaka;
      }
    }
    return dp[n];
  }

  int check(llint ocekivano) {
    if(!dobar_format()) {
      cerr << "krivi format!" << endl;
      return 0;
    }
    if(ima_ciklusa()) {
      cerr << "ima ciklusa!" << endl;
      return 0;
    }
    llint f = odredi_funkciju();
    if(ocekivano != f) {
      cerr << "vrijednosti funkcija se ne podudaraju!" << endl;
      cerr << "checker je izracunao: " << f << endl;
      return 0;
    }
    return 1;
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
  //cerr << t << ": " << g.n << " " << g.bridovi.size() << endl;
  g.ispis();
  assert(g.check(t));
}

int main() {
  llint t;
  cin >> t;
  pozovi(t);
  return 0;
}

