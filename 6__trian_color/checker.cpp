
// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<
#define debug(...) fprintf(stderr, __VA_ARGS__)
typedef long long ll;
typedef std::pair<int, int> pii;
#define X first
#define Y second
#define double long double
typedef double db;
using namespace std;

const string WRONG_OUTPUT_FORMAT = "Krivo formatiran izlaz.";
const string TEST_DATA_ERROR = "Greska u sluzbenom ulazu ili izlazu.";
const string WRONG = "Netocno.";
const string CORRECT = "Tocno.";
const string PARTIAL_FIRST = "Prvi red je tocan, drugi nije.";
const string ALARM = "Checker nije dobar.";

const int MaxN = 300300;

bool valid_color(int color) { return color >= 1 && color <= 3; }
bool other_color(int a, int b) { return 6 - a - b; }
bool valid_triangle(int a, int b, int c) { return (a + b + c == 6) && (a != b);}

int N;
vector<pii> adj[MaxN];
vector<pii> edge[MaxN];
map<pii, int> M;

/**
 * @param p fraction of points awarded to the contestant.
 * @pararm m error message displayed to the contestant.
 */
void finish(double p, const string& m);

int F[MaxN];

int lobit( int x ) { return x & -x; }

int query( int x ) {
  int sum = 0;
  for( ; x > 0; x -= lobit(x) ) sum += F[x];
  return sum;
}

void update( int x, int add ) {
  for( ; x <= N; x += lobit(x) ) F[x] += add;
}

bool check_triangulation() {
  FOR(i, 1, N+1) {
    sort(adj[i].begin(), adj[i].end());
    for(auto w: adj[i]) {
      int k = w.first;
      //   TRACE(i _ k);
      int sum = query(k-1) - query(i);
      if (sum != 0) return false;
    }
    for(auto w: adj[i]) {
      int k = w.first;
      update(i, 1);
      update(k, -1);
    }
  }
  return true;
}

bool check_colors() {
  FOR(i, 1, N+1) {
    for(auto &w: edge[i]) {
      w.first = (w.first + N - i) % N + 1; 
    }
    sort(edge[i].begin(), edge[i].end());
    for(auto &w: edge[i]) {
      w.first = (w.first + i - 1 ) % N; if (w.first == 0) w.first = N; 
    }
    
    FOR(p, 0, (int)edge[i].size() - 1) {
      int a = edge[i][p].second;
      int b = edge[i][p+1].second;
      int u = edge[i][p].first;
      int v = edge[i][p+1].first;

      if (u > v) swap(u, v);
      //  TRACE(i _ u _ v _ a _ b);
      int c = M[{u, v}];
      if (c == 0) finish(0, ALARM);
      
      if (!valid_triangle(a, b, c)) return false;
    }
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

  // Read official input

  string color_str;
  if (!(fin >> N) || !(fin >> color_str) || ((int)color_str.size() != N)) finish(0, TEST_DATA_ERROR);
  FOR(i, 1, N+1) {
    int color = color_str[i-1] - '0';
    if (!(color == 1 || color == 2 || color == 3)) finish(0, TEST_DATA_ERROR);
    int j = i%N + 1; 
    edge[i].push_back({j, color});
    edge[j].push_back({i, color});
    M[{min(i, j), max(i, j)}] = color;
  }

  // Read official output
  string official_answer;
  if (!(foff >> official_answer)) finish(0, TEST_DATA_ERROR);

  // Read contestant's output
  string contestant_answer;
  if (!(fout >> contestant_answer)) finish(0, WRONG_OUTPUT_FORMAT);
  //  std::transform(contestant_answer.begin(), contestant_answer.end(), contestant_answer.begin(), ::toupper);
  if (official_answer == "NE" && contestant_answer == "NE") finish(1.0, CORRECT);

  set<pii> diagonals;
  REP(i, N-3) {
    int u, v, color;
    if (!(fout >> u) || !(fout >> v) || !(fout >> color)) {
      finish(0, WRONG_OUTPUT_FORMAT);
    }
    if (u < 1 || u > N || v < 1 || v > N || v == u) finish(0, WRONG_OUTPUT_FORMAT);
    if (u > v) swap(u, v);
    if (v - u == 1 || (v == N && u == 1)) finish(0, WRONG_OUTPUT_FORMAT);
    pii diag = {u, v};
    if (diagonals.find(diag) != diagonals.end()) finish(0, WRONG);
    diagonals.insert(diag);

    adj[u].push_back({v, color});
    // adj[v].push_back({u, color}); WE DON'T DO THIS
    edge[u].push_back({v, color});
    edge[v].push_back({u, color});
    M[{u, v}] = color;
  }
  
  bool first_part = (contestant_answer == "DA");
  bool second_part = check_triangulation();
  //TRACE(second_part);
  second_part &= check_colors();
  //TRACE(second_part);
  
  if (first_part && second_part) {
    if (official_answer == "NE") finish(0.0, TEST_DATA_ERROR);
    finish(1.0, CORRECT);
  } else if (first_part) {
    finish(0.1, PARTIAL_FIRST);
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

