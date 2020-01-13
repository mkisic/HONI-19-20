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

int count_unique(int l, int r, string& s) {
    string t = s.substr(l - 1, r - l + 1);
    sort(t.begin(), t.end());
    return unique(t.begin(), t.end()) - t.begin();
}

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
  int n;
  string s;
  if (!(fin >> n) || !(fin >> s)) finish(0, TEST_DATA_ERROR);

  // Read official output
  int off_l, off_r;
  if (!(foff >> off_l) || !(foff >> off_r)) finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  int out_l, out_r;
  if (!(fout >> out_l) || !(fout >> out_r)) finish(0, WRONG_OUTPUT_FORMAT);
  if (!(1 <= out_l && out_l <= out_r && out_r <= n))
      finish(0, WRONG_OUTPUT_FORMAT);

  string smece;
  if (fout >> smece) finish(0, WRONG_OUTPUT_FORMAT);

  int off_cnt = count_unique(off_l, off_r, s);
  int out_cnt = count_unique(out_l, out_r, s);

  // Compare off_cnt/(off_r - off_l + 1) and out_cnt/(out_r - out_l + 1)
  int A = off_cnt * (out_r - out_l + 1);
  int B = out_cnt * (off_r - off_l + 1);
  if (A < B) finish(0, WRONG);
  else if (A == B) finish(1, CORRECT);
  else finish(0, TEST_DATA_ERROR);

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
