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

const int MAXN = 505;

bool check_answer(int r, int s, const string &dir, const vector<string> &grid) {
  if (r < 0 || r >= (int)grid.size() || s < 0 || s >= (int)grid[0].size())
    return false;
  if (grid[r][s] != '1') return false;
  if (dir != "DESNO" && dir != "DOLJE") return false;
  if (dir == "DESNO") {
    if (s + 1 >= (int)grid[0].size()) return false;
    if (grid[r][s + 1] != '0') return false;
  } else {
    if (r + 1 >= (int)grid.size()) return false;
    if (grid[r + 1][s] != '0') return false;
  }
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
  const string WRONG_ANS = "Prvi redak nije tocan.";
  const string WRONG_REC =
      "Prvi redak je tocan, ali rekonstrukcija nije tocna.";
  const string WRONG_REC_FORMAT =
      "Prvi redak je tocan, ali rekonstrukcija nije ispravno formatirana.";
  const string CORRECT = "Tocno.";

  // Read official input
  int R, S;
  vector<string> grid;

  if (!(fin >> R)) finish(0, TEST_DATA_ERROR);
  if (!(fin >> S)) finish(0, TEST_DATA_ERROR);

  for (int i = 0; i < R; ++i) {
    string row;
    if (!(fin >> row)) finish(0, TEST_DATA_ERROR);
    grid.push_back(row);
  }

  // Read official output (we only care about the first line)
  int official;
  if (!(foff >> official)) finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  int contestant;
  bool con_grid[MAXN][MAXN];
  memset(con_grid, false, sizeof con_grid);
  if (!(fout >> contestant)) finish(0, WRONG_OUTPUT_FORMAT);
  if (contestant != official) finish(0, WRONG_ANS);

  for (int i = 0; i < contestant; ++i) {
    int r, s;
    string dir;
    if (!(fout >> r)) finish(0.5, WRONG_REC_FORMAT);
    if (!(fout >> s)) finish(0.5, WRONG_REC_FORMAT);
    if (!(fout >> dir)) finish(0.5, WRONG_REC_FORMAT);
    --r; --s;
    if (!check_answer(r, s, dir, grid)) finish(0.5, WRONG_REC_FORMAT);
    int dr = 0, ds = 0;
    if (dir == "DESNO") ds = 1; else dr = 1;
    r += dr; s += ds;
    while (r < R && s < S && grid[r][s] == '0') {
      con_grid[r][s] = true;
      r += dr; s += ds;
    }
  }

  string smece;
  if (fout >> smece) finish(0.5, WRONG_REC_FORMAT);

  for (int i = 0; i < R; ++i)
    for (int j = 0; j < S; ++j)
      if (grid[i][j] == '0' && !con_grid[i][j])
        finish(0.5, WRONG_REC);

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
