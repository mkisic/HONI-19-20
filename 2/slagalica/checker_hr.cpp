// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <bits/stdc++.h>

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

bool fit(int a, int b) {
  return ((a == 1 || a == 3 || a == 5) && (b == 3 || b == 4 || b == 8)) ||
         ((a == 2 || a == 4 || a == 6) && (b == 1 || b == 2 || b == 7));
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
  const string PARTIAL = "Slagalica je ispravna, ali nije najmanja moguca.";
  const string CORRECT = "Tocno.";

  map<int, int> puzzle_type;

  // Read official input
  int n;
  if (!(fin >> n)) finish(0.0, TEST_DATA_ERROR);

  for (int i = 0; i < n; ++i) {
    int a, b;
    if (!(fin >> a)) finish(0.0, TEST_DATA_ERROR);
    if (!(fin >> b)) finish(0.0, TEST_DATA_ERROR);
    puzzle_type[b] = a;
  }

  // Read official output
  vector<int> sol_official;
  for (int i = 0; i < n; ++i) {
    int x;
    if (!(foff >> x)) finish(0.0, TEST_DATA_ERROR);
    sol_official.push_back(x);
    if (x == -1) break;
  }

  // Read contestant's output
  vector<int> sol_contestant;
  for (int i = 0; i < n; ++i) {
    int x;
    if (!(fout >> x)) finish(0.0, WRONG);
    sol_contestant.push_back(x);
    if (x == -1) break;
  }

  string smece;
  if (fout >> smece) finish(0.0, WRONG);

  if (sol_official == sol_contestant) finish(1.0, CORRECT);
  if (sol_official[0] == -1) finish(0.0, WRONG);

  bool ok = true;

  // prva i zadnja su rubne
  if (puzzle_type[sol_contestant.front()] != 5 &&
      puzzle_type[sol_contestant.front()] != 6) finish(0.0, WRONG);

  if (puzzle_type[sol_contestant.back()] != 7 &&
      puzzle_type[sol_contestant.back()] != 8) finish(0.0, WRONG);

  // sve oznake se pojavljuju tocno jednom i sve se pojavljuju u ulazu
  set<int> puzzle;
  for (int i = 0; i < n; ++i) {
    if (puzzle.find(sol_contestant[i]) != puzzle.end()) finish(0.0, WRONG);
    if (puzzle_type.find(sol_contestant[i]) == puzzle_type.end()) finish(0.0, WRONG);
    puzzle.insert(sol_contestant[i]);
  }

  for (int i = 1; i < n; ++i)
    if (!fit(puzzle_type[sol_contestant[i - 1]], puzzle_type[sol_contestant[i]]))
      finish(0.0, WRONG);

  finish(0.4, PARTIAL);
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
