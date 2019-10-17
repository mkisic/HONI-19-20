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

typedef long long llint;
typedef long long ll;

/**
 * @param p fraction of points awarded to the contestant.
 * @pararm m error message displayed to the contestant.
 */
void finish(double p, const string& m);


bool prime(ll x) {
  if (x < 2) return 0;
  for (ll i = 2; i * i <= x; i++) {
    if (x % 2 == 0) return 0;
  }
  return 1;
}

bool range(ll x) {
  if (x < 2 || x > 1e15) return 0;
  return 1;
}

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
  const string PREVISE = "Previse brojeva u nizu.";
  const string OUT_OF_RANGE = "Broj u nizu je prevelik ili premalen.";

  // Read official input
  ll a, b;

  if (!(fin >> a)) finish(0.0, TEST_DATA_ERROR);
  if (!(fin >> b)) finish(0.0, TEST_DATA_ERROR);

  // Read official output
  int n_official;
  if (!(foff >> n_official)) finish(0.0, TEST_DATA_ERROR);
  
  vector <ll> v_official;
  if (n_official != -1) {
    REP(i, n_official) {
      ll x;
      if (!(foff >> x)) finish(0.0, TEST_DATA_ERROR);
      v_official.push_back(x);
    }
  }

  // Read contestant's output
  int n_output;
  if (!(fout >> n_output)) finish(0.0, WRONG_OUTPUT_FORMAT);

  if (n_output == -1 || n_official == -1) {
    if (n_official == n_output) {
      string smece;
      if (fout >> smece) finish(0.0, WRONG_OUTPUT_FORMAT);
      finish(1.0, CORRECT);
    } else {
      finish(0.0, WRONG);
    }
    return;
  }

  if (n_output <= 0) finish(0.0, WRONG);
  if (n_output > 30) finish(0.0, PREVISE);

  vector <ll> v_output;
  REP(i, n_output) {
    ll x;
    if (!(fout >> x)) finish(0.0, TEST_DATA_ERROR);
    v_output.push_back(x);
  }

  string smece;
  if (fout >> smece) finish(0.0, WRONG_OUTPUT_FORMAT);

  bool ok = 1;

  if (v_official[0] != v_output[0]) ok = 0;
  if (v_official.back() != v_output.back()) ok = 0;

  for (auto x : v_output) {
    if (!range(x)) finish(0.0, OUT_OF_RANGE);
    if (!prime(x)) ok = 0;
  }

  REP(i, (int)v_output.size() - 1) {
    if (!prime(abs(v_output[i] - v_output[i + 1]))) ok = 0;
  }

  if (ok) {
    finish(1.0, CORRECT);
  } else {
    finish(0.0, WRONG);
  }

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
