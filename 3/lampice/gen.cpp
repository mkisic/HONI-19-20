#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100100;

int n;
int k;  // velicina alfabeta
char input[MAXN];
vector<int> adj[MAXN];
vector<int> mapping;  // permutacija
string type;  // strategija za generiranje
bool mapping_applied = false;
vector<pair<int, int>> E;
int deep_diff;
int reset_iters;

void add_edge(int i, int j) {
  adj[i].push_back(j);
  adj[j].push_back(i);
  if (rand() % 2) {
    E.push_back({i, j});
  } else {
    E.push_back({j, i});
  }
}

void init(int argc, char **argv) {
  n = atoi(argv[2]);
  k = atoi(argv[3]);
  type = string(argv[4]);
  mapping.resize(n);
  iota(mapping.begin(), mapping.end(), 0);
  reset_iters = 10 + rand() % 5;
  if (type.substr(0, 4) == "deep") {
    deep_diff = max(20, n / 1000);
    if (argc >= 6) deep_diff = atoi(argv[5]);
    if (type == "deep-reset" && argc >= 7)
      reset_iters = atoi(argv[6]);
  }
}

void gen_tree_simple() {
  for (int i = 1; i < n; ++i) {
    int j = rand() % i;
    add_edge(i, j);
  }
}

void gen_chain() {
  for (int i = 1; i < n; ++i) {
    adj[i].push_back(i - 1);
    adj[i - 1].push_back(i);
    E.push_back({i - 1, i});
  }
}

void gen_tree_deep() {
  for (int i = 1; i < n; ++i) {
    int j = i - 1 - rand() % min(deep_diff, i);
    add_edge(i, j);
  }
}

void gen_tree_shallow() {
  int diff = max(50, n / 200);
  for (int i = 1; i < n; ++i) {
    int j = rand() % min(diff, i);
    add_edge(i, j);
  }
}

void gen_input_simple() {
  for (int i = 0; i < n; ++i)
    input[i] = 'a' + rand() % k;
}

vector<int> calc_path(int, int);

void gen_input_longpalin() {
  string palin = string(1, 'a' + rand() % k);
  while (palin.size() < n) {
    string between = "";
    if (rand() % 5)
      between = string(1, 'a' + rand() % k);
    palin = palin + between + palin;
  }
  
  vector<int> dist(n, -1);
  queue<int> q;
  
  int mid = n / 2;
  dist[mid] = 0;
  q.push(mid);
  if (rand() % 2 == 0) {
    assert(!adj[mid].empty());
    int nmid = adj[mid][0];
    dist[nmid] = 0;
    q.push(nmid);
  }

  for (; !q.empty(); q.pop()) {
    int x = q.front();
    for (int y : adj[x]) {
      if (dist[y] != -1) continue;
      dist[y] = dist[x] + 1;
      q.push(y);
    }
  }
  
  int D = calc_path(0, n - 1).size() / 2 - 15;

  for (int i = 0; i < n; ++i) {
    assert(dist[i] >= 0);
    input[i] = palin[dist[i]];
    if (dist[i] > D && rand() % 10 == 0)
      input[i] = 'a' + rand() % k;
  }
}

void gen_input_reset() {
  for (int i = 0; i < n; ++i)
    input[i] = 'a';
  for (int i = 0; i < reset_iters; ++i)
    input[rand() % n] = 'a' + rand() % k;
}

vector<int> calc_path(int u, int v) {
  vector<bool> vis(n, false);
  vector<int> dad(n, -1);
  queue<int> q;
  
  vis[u] = true;
  for (q.push(u); !q.empty(); q.pop()) {
    int x = q.front();
    for (int y : adj[x]) {
      if (vis[y]) continue;
      vis[y] = true;
      dad[y] = x;
      q.push(y);
    }
  }

  vector<int> path;
  for (int x = v; x != -1; x = dad[x])
    path.push_back(x);
  return path;
}

void apply_reverse() {
  int reps = max(10, n / 2000);
  for (int i = 0; i < reps; ++i) {
    int x = rand() % n;
    int y = rand() % n;
    vector<int> path = calc_path(x, y);
    for (int j = 0; j < (int)path.size() / 2; ++j) {
      int jj = (int)path.size() - 1 - j;
      input[path[jj]] = input[path[j]];
    }
  }
}

void apply_mapping() {
  mapping_applied = true;
  random_shuffle(mapping.begin(), mapping.end());
}

void output() {
  cout << n << endl;
  static char mapped_input[MAXN];
  for (int i = 0; i < n; ++i)
    mapped_input[mapping[i]] = input[i];
  mapped_input[n] = 0;
  cout << mapped_input << endl;
  if (mapping_applied)
    random_shuffle(E.begin(), E.end());
  for (auto it : E)
    cout << mapping[it.first] + 1 << " " << mapping[it.second] + 1 << endl;
}

int main(int argc, char **argv) {
  int seed = atoi(argv[1]);
  srand(seed);
  
  init(argc, argv);
  
  if (type == "simple-simple") {
    gen_tree_simple();
    gen_input_simple();
    apply_mapping();
  } else if (type == "chain-simple") {
    gen_chain();
    gen_input_simple();
  } else if (type == "simple-reverse") {
    gen_tree_simple();
    gen_input_simple();
    apply_reverse();
    apply_mapping();
  } else if (type == "chain-reverse") {
    gen_chain();
    gen_input_simple();
    apply_reverse();
  } else if (type == "deep-simple") {
    gen_tree_deep();
    gen_input_simple();
    apply_mapping();
  } else if (type == "deep-reverse") {
    gen_tree_deep();
    gen_input_simple();
    apply_reverse();
    apply_mapping();
  } else if (type == "shallow-simple") {
    gen_tree_shallow();
    gen_input_simple();
    apply_mapping();
  } else if (type == "shallow-reverse") {
    gen_tree_shallow();
    gen_input_simple();
    apply_reverse();
    apply_mapping();
  } else if (type == "deep-longpalin") {
    gen_tree_deep();
    gen_input_longpalin();
    apply_mapping();
  } else if (type == "deep-reset") {
    gen_tree_deep();
    gen_input_reset();
    apply_mapping();
  } else if (type == "chain-longpalin") {
    gen_chain();
    gen_input_longpalin();
  } else {
    assert(false);
  }

  output();

  return 0;
}
