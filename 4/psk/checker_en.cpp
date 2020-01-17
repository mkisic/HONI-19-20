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

typedef long long ll;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

const int MAXN = 1010;

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
  const string WRONG = "Wrong answer.";
  const string CORRECT = "Correct.";
  const string PRVA = "First line is correct, second one is not.";
  const string DRUGA = "Second line is correct, first one is not.";

  // Read official input
  int n;
  int A[MAXN], B[MAXN];
  int p[MAXN];

  ll tot = 0;
  if (!(fin >> n)) finish(0.0, TEST_DATA_ERROR);
  REP(i, n) {
    if (!(fin >> A[i])) finish(0.0, TEST_DATA_ERROR);
    if (!(fin >> B[i])) finish(0.0, TEST_DATA_ERROR);
    tot += A[i];
  }

  // Read official output  -------------- ovo mi NIJE BITNO u ovom zadatku
  int official_output_val;
  if (!(foff >> official_output_val)) finish(0.0, TEST_DATA_ERROR);

  // Read contestant's output
  int m;
  if (!(fout >> m)) finish(0.0, WRONG_OUTPUT_FORMAT);
  

  bool prva = (official_output_val == m);
  bool druga = 1;
  
  ll sum = 0;
  int nule = 0;

  REP(i, n) {
    if (!(fout >> p[i])) druga = 0;
    sum += p[i];
    nule += (p[i] == 0);
    if (druga && p[i] > B[i] || p[i] < 0) druga = 0;
  }

  if (sum != tot || nule != official_output_val) druga = 0;

  string smece;
  if (fout >> smece) finish(0.0, WRONG_OUTPUT_FORMAT);


  if (prva && druga) finish(1.0, CORRECT);
  if (prva && !druga) finish(0.8, PRVA);
  if (!prva && druga) finish(0.2, DRUGA);
  if (!prva && !druga) finish(0.0, WRONG);

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
