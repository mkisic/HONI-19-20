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

const int MaxS = 1100;
const int MaxN = 2*MaxS;
const int Mod = 1e9 + 7;

void NO() {
  cout << "NE" << endl;
  exit(0);
}
void YES() {
  cout << "DA" << endl;
}
inline void match(int i, int j) {
  cout << i + 1 << " " << j + 1 << endl;
}

int N;
int S = 1005;
int a[MaxN], b[MaxN];
map<int, vector<int>> row_mem, col_mem;
vector<int> adj[MaxN];
bool been[MaxN];
vector<vector<int>> paths;
vector<vector<int>> cycles;

struct Event {
  int i, j;
  bool vert;
  int group; // -1 for paths, index for cycles

  Event(int i_, int j_, int group_ ) : i(i_), j(j_), group(group_) {
    vert = (b[i] == b[j]); 
  }
};
vector<Event> events;

// graph of horizontal cycles
int C;
vector<int> edge[MaxN];
int color[MaxN]; // 1 - hor, 2 - ver
bool seen[MaxN];

void dfs_graph(int i) {
  seen[i] = 1;
  assert(color[i] == 1);
  
  for (auto j: edge[i]) {
    if (color[j] == 2) {
      NO();
    }
    color[j] = 1;
    dfs_graph(j);
  }
}

void solve() {
  REP(i, C) {
    if (!seen[i] && color[i] == 1) dfs_graph(i);
  } 

  YES();
  for (auto &path: paths) {
    for (int i = 0; i < (int)path.size(); i += 2) {
      match(path[i], path[i+1]);
    }
  }
  REP(k, C) {
    auto &cycle = cycles[k];
    bool off = 0;
    off ^= (color[k] == 1);
    off ^= (a[cycle[0]] == a[cycle[1]]);

    int z = 1;
    if (off) {
      z = -1;
    }
    for (int i = 0; i < (int)cycle.size(); i += 2) {
      int j = i + z;
      if (j < 0) j += (int)cycle.size();
      if (j >= (int)cycle.size()) j -= (int)cycle.size();	
      match(cycle[i], cycle[j]);
    }
  }
  
}

bool segments_intersect(pair<int, int> A, pair<int, int> B) {
  // horizontal, vertical
  assert((a[A.X] == a[A.Y]));
  assert((a[B.X] != a[B.Y]));

  int hr = a[A.X];
  int vr = b[B.X];
  assert(b[B.Y] == vr);

  if (b[A.X] > b[A.Y]) swap(A.X, A.Y);
  if (a[B.X] > a[B.Y]) swap(B.X, B.Y);

  return (a[B.X] <= hr) && (hr <= a[B.Y])
    && (b[A.X] <= vr) && (vr <= b[A.Y]);  
}

void intersect_events(Event &A, Event &B) { // horizontal, vertical
  if (A.vert || !B.vert) return;
  if (!segments_intersect({A.i, A.j}, {B.i, B.j})) return;

  if (A.group == -1) {
    if (B.group == -1 || color[B.group] == 2) {
      NO();
    }
    color[B.group] = 1; 
  }
  else if (B.group == -1) {
    if (color[A.group] == 1){
      NO();
    }
    color[A.group] = 2;
  }
  else {
    edge[A.group].push_back(B.group);
  }
}

void make_graph() {
  int E = (int)events.size();
  REP(i, E) REP(j, E) if (i != j) {
    intersect_events(events[i], events[j]);
  }
}


void make_events() {
  for (auto &path: paths) {
    assert((int)path.size() % 2 == 0);
    for (int i = 0; i < (int)path.size(); i += 2) {
      events.push_back(Event(path[i], path[i+1], -1));
    }
  }
  
  C = (int)cycles.size();
  for (int k = 0; k < C; k++) {
    auto &cycle = cycles[k];
    for (int i = 0; i < (int)cycle.size(); i++) {
      int j = i + 1;
      if (j >= (int)cycle.size()) j = 0;
      events.push_back(Event(cycle[i], cycle[j], k));
    }
  }
}

void connect(int i, int j) {
  adj[i].push_back(j);
  adj[j].push_back(i);
}

void dfs_cycle(int i, int parent, int start) {
  assert(!been[i]);
  assert((int)adj[i].size() == 2);
  been[i] = 1;
  cycles.back().push_back(i);
  for (auto j: adj[i]) {
    if (j != parent) {
      if (j == start) return;
      dfs_cycle(j, i, start);
    }
  }
}

void dfs_path(int i, int parent) {
  assert(!been[i]);
  been[i] = 1;
  paths.back().push_back(i);
  for (auto j: adj[i]) {
    if (j != parent) {
      dfs_path(j, i);
    }
  }
}

void make_adj() {
  for (auto &elem: row_mem) {
    //    assert((int)elem->second.size() <= 2);
    
    if ((int)elem.second.size() == 2) {
      connect(elem.second[0], elem.second[1]);
    }

  }
  for (auto &elem: col_mem) {
    //    assert((int)elem->second.size() <= 2);

    if ((int)elem.second.size() == 2) {
      connect(elem.second[0], elem.second[1]);
    }
  }
}

void make_cycles_and_paths() {
  make_adj();
  REP(i, N) assert((int)adj[i].size() <= 2);
  REP(i, N) {
    if (!been[i] && (int)adj[i].size() <= 1) {
      paths.emplace_back();
      dfs_path(i, -1);

      // check if paths are of even size
      if ((int)paths.back().size() % 2 == 1) {
	NO();
      }
    }
  }

  REP(i, N) {
    if (!been[i]) {
      cycles.emplace_back();
      dfs_cycle(i, adj[i][0], i);
    }
  }
  
}

void load() {
  cin >> N;
  REP(i, N) {
    cin >> a[i] >> b[i];
    row_mem[a[i]].push_back(i);
    col_mem[b[i]].push_back(i);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  load();
  make_cycles_and_paths();
  make_events();
  make_graph();
  solve();
  return 0;
}


