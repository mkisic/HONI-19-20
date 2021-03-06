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
typedef unsigned int uint;
using namespace std;

const int MaxN = 200100;
const int Mod = 1e9 + 7;

int N;
int b[MaxN];

struct Edge {
  int X, Y;
   
  Edge(int x, int y) : X(min(x, y)), Y(max(x, y)) { }

  friend bool operator<(Edge &A, Edge &B) {
    if (A.X == B.X) return A.Y < B.Y;
    return A.X < B.X;
  }
};

struct Triangulation {
  set<Edge> edges;
};

bool isGood(Triangulation& T) {
  vector<int> deg(N, 0);
  for (auto E: T.edges) {
    deg[E.X]++;
    deg[E.Y]++;
  }

  
}

void solve() {

}

void load() {
  cin >> N;
  REP(i, N) {
    cin >> b[i];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  load();	
  solve();
  return 0;
}


