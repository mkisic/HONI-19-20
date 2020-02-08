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

#define fi first
#define se second

typedef pair<int, int> pii;

const int INF = 1e9;
const int MAXN = 1e5 + 10;

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

  // Read official input
  int n;
  if (!(fin >> n)) finish(0, TEST_DATA_ERROR);
  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
      if (!(fin >> x[i]) || !(fin >> y[i])) finish(0, TEST_DATA_ERROR);
      x[i]--;
      y[i]--;
  }

  // Read official output
  string off_ans;
  if (!(foff >> off_ans)) finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  string out_ans;
  if (!(fout >> out_ans)) finish(0, WRONG_OUTPUT_FORMAT);

  if (out_ans != "DA") {
      string smece;
      if (fout >> smece) finish(0, WRONG_OUTPUT_FORMAT);

      if (out_ans == off_ans) finish(1, CORRECT);
      else finish(0, WRONG);
  }

  vector<vector<int>> in(MAXN), out(MAXN);
  vector<vector<pii>> query(MAXN);
  vector<bool> matched(n, false);
  for (int i = 0; i < n / 2; i++) {
      int a, b;
      if (!(fout >> a) || !(fout >> b)) finish(0, WRONG_OUTPUT_FORMAT);
      if (!(1 <= a && a <= n) || !(1 <= b && b <= n))
          finish(0, WRONG_OUTPUT_FORMAT);
      a--; b--;
      if (matched[a] || matched[b] || a == b) finish(0, WRONG);
      matched[a] = matched[b] = true;
      if (x[a] == x[b]) {
          int l = y[a], r = y[b];
          if (l > r) swap(l, r);
          query[x[a]].push_back({l, r});
      } else if (y[a] == y[b]) {
          int l = x[a], r = x[b];
          if (l > r) swap(l, r);
          in[l].push_back(y[a]);
          out[r].push_back(y[a]);
      } else {
          finish(0, WRONG);
      }
  }
  string smece;
  if (fout >> smece) finish(0, WRONG_OUTPUT_FORMAT);

  set<int> S = {INF};
  for (int i = 0; i < MAXN; i++) {
      for (int a : in[i]) S.insert(a);
      for (auto p : query[i])
          if (*S.lower_bound(p.fi) <= p.se) finish(0, WRONG);
      for (int a : out[i]) S.erase(a);
  }

  if (off_ans == "DA") finish(1, CORRECT);
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
