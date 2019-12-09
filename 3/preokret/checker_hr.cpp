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
  const string PRVA = "Tocan prvi redak.";
  const string DRUGA = "Tocan drugi redak.";
  const string TRECA = "Tocan treci redak.";
  const string PRVADRUGA = "Tocni su prvi i drugi redak.";
  const string PRVATRECA = "Tocni su prvi i treci redak.";
  const string DRUGATRECA = "Tocni su drugi i treci redak.";

  // Read official input ---------------- ovo mi NIJE BITNO u ovom zadatku
  // int n;
  // if (!(fin >> n)) finish(0.0, TEST_DATA_ERROR);

  // Read official output
  string a, b, c;
  if (!getline(foff, a)) finish(0.0, TEST_DATA_ERROR);
  if (!getline(foff, b)) finish(0.0, TEST_DATA_ERROR);
  if (!getline(foff, c)) finish(0.0, TEST_DATA_ERROR);

  // Read contestant's output
  string A, B, C;
  if (!getline(fout, A)) A = "";
  if (!getline(fout, B)) B = "";
  if (!getline(fout, C)) C = "";

  string smece;
  if (fout >> smece) finish(0.0, WRONG_OUTPUT_FORMAT);

  if (a != A && b != B && c != C) finish(0.0, WRONG);
  if (a == A && b != B && c != C) finish(0.2, PRVA);
  if (a != A && b == B && c != C) finish(0.2, DRUGA);
  if (a != A && b != B && c == C) finish(0.6, TRECA);
  if (a == A && b == B && c != C) finish(0.4, PRVADRUGA);
  if (a == A && b != B && c == C) finish(0.8, PRVATRECA);
  if (a != A && b == B && c == C) finish(0.8, DRUGATRECA);
  if (a == A && b == B && c == C) finish(1.0, CORRECT);

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
