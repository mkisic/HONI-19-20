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

/**
 * @param p fraction of points awarded to the contestant.
 * @pararm m error message displayed to the contestant.
 */
void finish(double p, const string& m);

vector<string> split(const string &a, const string& delim) {
  vector<string> ans;
  int ptr = 0;
  for (size_t f_pos; (f_pos = a.find(delim, ptr)) != string::npos; ) {
    ans.push_back(a.substr(ptr, f_pos - ptr));
    ptr = f_pos + delim.size();
  }
  ans.push_back(a.substr(ptr));
  return ans;
}

bool check_second_part(int official_val, string c_recon,
                       string target, const vector<string>& dict) {
  vector<string> tokens = split(c_recon, "|");

  if ((int)tokens.size() != official_val) {
    return false;
  }

  string concat = "";
  set<string> set_dict(dict.begin(), dict.end());
  REP(i, (int)tokens.size()) {
    const string& tok = tokens[i];
    if (set_dict.count(tok) == 0)
      return false;
    concat += tok;
  }

  if (concat.find(target) == string::npos)
    return false;

  return true;
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
  const string PARTIAL_FIRST = "Prvi red je tocan, drugi nije.";

  // Read official input
  string target;
  int n_dict;
  vector<string> dict;

  if (!(fin >> target)) finish(0, TEST_DATA_ERROR);
  if (!(fin >> n_dict)) finish(0, TEST_DATA_ERROR);

  REP(i, n_dict) {
    static string x;
    if (!(fin >> x)) finish(0, TEST_DATA_ERROR);
    dict.push_back(x);
  }

  // Read official output
  int official_output_val;
  if (!(foff >> official_output_val)) finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  int c_output;
  if (!(fout >> c_output)) finish(0, WRONG_OUTPUT_FORMAT);

  string c_recon;
  if (!(fout >> c_recon)) {
    // might not output the second line
    c_recon = "";
  }

  bool first_part = (official_output_val == c_output);
  bool second_part = check_second_part(official_output_val, c_recon, target, dict);

  if (first_part && second_part) {
    finish(1.0, CORRECT);
  } else if (first_part) {
    finish(0.5, PARTIAL_FIRST);
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
