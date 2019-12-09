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
  const string WRONG_OUTPUT_FORMAT = "Wrong output format.";
  const string TEST_DATA_ERROR = "Test data error.";
  const string WRONG = "Wrong.";
  const string CORRECT = "Correct.";

  // Read official input
  int n, k;
  if (!(fin >> n) || !(fin >> k)) finish(0, TEST_DATA_ERROR);

  // Read official output  -------------- ovo mi NIJE BITNO u ovom zadatku
  // int official_output_val;
  // if (!(foff >> official_output_val)) finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  vector<int> a, b;

  for (int i = 0; i < k; i++) {
      int x, y;
      if (!(fout >> x) || !(fout >> y)) finish(0, WRONG_OUTPUT_FORMAT);
      if (!(0 <= x && x < k && n - k <= y && y < n))
          finish(0, WRONG_OUTPUT_FORMAT);
      if ((x & y) != x) finish(0, WRONG);

      a.push_back(x);
      b.push_back(y);
  }

  string smece;
  if (fout >> smece) finish(0, WRONG_OUTPUT_FORMAT);

  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  if ((int)a.size() != k || (int)b.size() != k) finish(0, WRONG);

  finish(1, CORRECT);

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
