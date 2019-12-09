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

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

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
void checker(ifstream& fin, ifstream& foff, ifstream& fout)
{
  const string WRONG_OUTPUT_FORMAT = "Krivo formatiran izlaz.";
  const string TEST_DATA_ERROR = "Greska u sluzbenom ulazu ili izlazu.";
  const string WRONG = "Netocno.";
  const string CORRECT = "Tocno.";
  const string NOT_ARIT = "Nizovi nisu aritmeticki nizovi.";

  // Read official input
  int n;
  multiset <int> s;

  if (!(fin >> n)) finish(0.0, TEST_DATA_ERROR);

  REP(i, n) {
    int x;
    if (!(fin >> x)) finish(0.0, TEST_DATA_ERROR);
    s.insert(x);
  }

  // Read official output
  int official_output_val;
  if (!(foff >> official_output_val)) finish(0.0, TEST_DATA_ERROR);

  // Read contestant's output
  int a, b;
  if (!(fout >> a)) finish(0.0, WRONG_OUTPUT_FORMAT);
  
  if (official_output_val == -1 && a != -1) finish(0.0, WRONG);
  if (a == -1) finish(0.0, WRONG);
  
  multiset <int> cont;

  vector <int> v[2], v1[2];
  REP(i, a) {
    int x;
    if (!(fout >> x)) finish(0.0, WRONG_OUTPUT_FORMAT);
    cont.insert(x);
    v[0].push_back(x);
  }

  if (!(fout >> b)) finish(0.0, WRONG_OUTPUT_FORMAT);

  if (a + b != n || a <= 0 || b <= 0 || a >= n || b >= n) finish(0.0, WRONG);

  REP(i, b) {
    int x;
    if (!(fout >> x)) finish(0.0, WRONG_OUTPUT_FORMAT);
    cont.insert(x);
    v[1].push_back(x);
  }

  string smece;
  if (fout >> smece) finish(0.0, WRONG_OUTPUT_FORMAT);

  if (cont != s) finish(0.0, WRONG);
  if ((int)v[0].size() != a || (int)v[1].size() != b) finish(0.0, WRONG);
  
  REP(i, 2) {
    v1[i] = v[i];
    sort(v1[i].begin(), v1[i].end());
    if (v1[i] != v[i]) finish(0.0, WRONG);
  }

  REP(j, 2) {
    FOR(i, 1, (int)v[j].size()) if (v[j][i] - v[j][i - 1] != v[j][1] - v[j][0]) finish(0.0, NOT_ARIT);  
  }

  finish(1.0, CORRECT);

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
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout);
  assert(false); // checker must terminate via finish() before exiting!

  return 0;
}
