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

bool number_check(string s) {
  if ((int)s.size() > 3) return 0; // pazi na ovo ako se promjeni ogranicenje
  if (s[0] == '0') return 0; // ni 0 nije dozvoljen pa je ovo ok
  return 1;
}

int convert(string s) {
  int ret = 0;
  REP(i, (int)s.size()) {
    ret *= 10;
    ret += s[i] - '0';
  }
  return ret;
}

bool check(string s, int n) {
  string all = "0123456789+";
  for (auto c : s) {
    bool ok = 0;
    for (auto t : all) if (c == t) ok = 1;
    if (!ok) return 0;
  }

  if (s[0] == '+' || s[(int)s.size()-1] == '+') return 0;
  string tmp = "";

  int suma = 0;
  REP(i, (int)s.size()) {
    if (s[i] == '+') {
      if (tmp == "") return 0;
      if (!number_check(tmp)) return 0;
      suma += convert(tmp);
      tmp = "";
    } else {
      tmp += s[i];
    }
  }
  if (tmp != "") {
    if (!number_check(tmp)) return 0;
    suma += convert(tmp);
  } else {
    return 0;
  }
  return suma == n;
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

  // Read official input
  int n;

  if (!(fin >> n)) finish(0.0, TEST_DATA_ERROR);

  // Read official output  -------------- ovo mi NIJE BITNO u ovom zadatku
  // int official_output_val;
  // if (!(foff >> official_output_val)) finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  string out;
  if (!(fout >> out)) finish(0.0, WRONG_OUTPUT_FORMAT);

  string smece;
  if (fout >> smece) finish(0.0, WRONG_OUTPUT_FORMAT);

  if (!check(out, n)) finish(0.0, WRONG);

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
