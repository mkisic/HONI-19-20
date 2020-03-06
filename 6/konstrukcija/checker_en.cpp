// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

struct graf {
  int n;
  vector<par> bridovi;
  vector<vector<int> > djeca;
  vector<vector<int> > roditelji;
  graf(int _n, vector<par> _bridovi) {
    n = _n;
    bridovi = _bridovi;
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
    map<par, int> brojac;
    for(auto p : bridovi) {
      if(brojac[p] > 0) return 0;
      brojac[p]++;
    }
    return 1;
  }

  int dfs(int cvor, vector<int> &boja) {
    if(boja[cvor] == 1) return 0;
    if(boja[cvor] == 2) return 1;
    boja[cvor] = 1;
    int ret = 1;
    for(auto kamo : djeca[cvor])
      ret &= dfs(kamo, boja);
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

  void topoloski(int cvor, vector<int> &bio, vector<int> &v) {
    if(bio[cvor]) return;
    bio[cvor] = 1;
    for(auto kamo : roditelji[cvor])
      topoloski(kamo, bio, v);
    v.push_back(cvor);
  }

  void odredi_pretke(int cvor, vector<int> &imam, vector<int> &v) {
    if(imam[cvor]) return;
    imam[cvor] = 1;
    v.push_back(cvor);
    for(auto kamo : roditelji[cvor])
      odredi_pretke(kamo, imam, v);
  }

  vector<int> poredak;
  vector<vector<int> > preci;

  void odredi_topoloski_poredak() {
    vector<int> bio(n + 1);
    FOR(i, 1, n + 1)
      if(!bio[i])
        topoloski(i, bio, poredak);
  }
  
  void odredi_pretke() { 
    preci = vector<vector<int> > (n + 1);
    FOR(i, 1, n + 1) {
      vector<int> imam(n + 1);
      odredi_pretke(i, imam, preci[i]);
    }
  }

  __int128 odredi_funkciju() {
    vector<__int128> dp(n + 1);
    for(auto x : poredak) {
      if(x == 1)
        dp[x] = 1;
      else {
        __int128 suma_predaka = 0;
        for(auto v : preci[x])
          suma_predaka += dp[v];
        dp[x] = -1 * suma_predaka;
      }
    }
    return dp[n];
  }

  void postavi_djecu_i_roditelje() {
    djeca = vector<vector<int> > (n + 1);
    roditelji = vector<vector<int> > (n + 1);
    for(auto p : bridovi) {
      djeca[p.X].push_back(p.Y);
      roditelji[p.Y].push_back(p.X);
    }
  }

  int ispitaj_napetosti(int pocetak) { 
    const __int128 GRANICA = (__int128)1 << 80;
    vector<__int128> dp(n + 1);
    for(auto x : poredak) {
      if(x == pocetak)
        dp[x] = 1;
      else {
        __int128 suma_predaka = 0;
        for(auto v : preci[x])
          suma_predaka += dp[v];
        dp[x] = -1 * suma_predaka;
      }
      if(dp[x] > GRANICA || -1 * dp[x] > GRANICA) return 1;
    }
    return 0;
  }

  int prevelike_napetosti() {
    FOR(i, 1, n + 1)
      if(ispitaj_napetosti(i))
        return 1;
    return 0;
  }

  int check(llint ocekivano, string &poruka) {    
    const string WRONG_OUTPUT_FORMAT = "Wrong output format.";
    const string WRONG = "Wrong answer.";
    const string CORRECT = "Correct.";
    const string NOT_DIRECTED_GRAPH = "Wrong graph format";
    if(!dobar_format()) {
      poruka = WRONG_OUTPUT_FORMAT;
      return 0;
    }
    postavi_djecu_i_roditelje();
    if(ima_ciklusa()) {
      poruka = NOT_DIRECTED_GRAPH;
      return 0;
    }
    odredi_topoloski_poredak();
    odredi_pretke();
    __int128 f = odredi_funkciju();
    if(ocekivano != f) {
      poruka = WRONG;
      return 0;
    } 
    if(prevelike_napetosti()) {    //ispitujem napetosti, tek nakon sto je rezultat u cvoru n dobar
      poruka = WRONG_OUTPUT_FORMAT;//tako da ce se checker skoro sigurno dugo izvrsavati samo na 
      return 0;                    //tocnim rjesenjima
    }
    poruka = CORRECT;
    return 1;
  }
};


/**
 * @param p fraction of points awarded to the contestant.
 * @pararm m error message displayed to the contestant.
 */
void finish(double p, const string& m);

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream& fin, ifstream& fout)
{
  const string WRONG_OUTPUT_FORMAT = "Wrong output format.";
  const string TEST_DATA_ERROR = "Error in official input";
  const string TOO_BIG_N_OR_M = "Number of nodes/edges limit exceeded.";

  // Read official input
  llint K;

  if (!(fin >> K)) finish(0.0, TEST_DATA_ERROR);

  // Official output has been ignored
  
  // Read contestant's output 
  int n, m;
  vector<par> bridovi;
  if (!(fout >> n)) finish(0.0, WRONG_OUTPUT_FORMAT);
  if (!(fout >> m)) finish(0.0, WRONG_OUTPUT_FORMAT);
  if(n < 1) finish(0.0, WRONG_OUTPUT_FORMAT);
  if(m < 0) finish(0.0, WRONG_OUTPUT_FORMAT);
  if(n > 1000 || m > 1000) finish(0.0, TOO_BIG_N_OR_M);
  REP(i, m) {
    int x, y;
    if (!(fout >> x)) finish(0.0, WRONG_OUTPUT_FORMAT);
    if (!(fout >> y)) finish(0.0, WRONG_OUTPUT_FORMAT);
    bridovi.push_back(par(x, y));
  }
 
  string smece;
  if (fout >> smece) finish(0.0, WRONG_OUTPUT_FORMAT);
  
  graf g(n, bridovi);
  string poruka;
  int t = g.check(K, poruka);
  if(!t) finish(0.0, poruka);
  else finish(1.0, poruka);

  // The function MUST terminate before this line via finish()!
}

void finish(double p, const string& m) {
  cout << p << endl;
  cout << m << endl;
  exit(0);
}

int main(int argc, char *argv[])
{
  assert(argc == 4);

  ifstream fin(argv[1]);
  ifstream fout(argv[3]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, fout);
  assert(false); // checker must terminate via finish() before exiting!

  return 0;
}

