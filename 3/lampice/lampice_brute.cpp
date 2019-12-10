#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long ll;

const int MAXN = 100100;

int n;
char input[MAXN];
vector<int> adj[MAXN];

template<typename T>
ostream& operator<<(ostream &os, vector<T> v) {
  os << "[";
  for (int i = 0; i < (int)v.size(); ++i) {
    if (i > 0) os << ", ";
    os << v[i];
  }
  os << "]";
  return os;
}

ostream& operator<<(ostream &os, pair<int, int> p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

bool ok(const vector<pair<int, int>> &vec) {
  for (int i = 1; i < (int)vec.size(); ++i)
    if (vec[i].second != vec[i - 1].second)
      return true;
  return false;
}

int solve(int x) {
  static vector<int> history;
  static vector<pair<int, int>> nvec[128];
  static vector<vector<pair<int, int>>> V;
  static bool done[MAXN];
  V.resize(1);
  V[0].push_back({x, -1});

  int ret = 1;
  for (int len = 1; !V.empty(); ++len) {
    vector<vector<pair<int, int>>> NV;

    //TRACE(V);

    for (auto &vec : V) {
      for (auto it : vec) {
        done[it.first] = true;
        history.push_back(it.first);
      }
    }

    for (auto &vec : V) {
      for (auto it : vec) {
        if (it.first < n)
          ret = max(ret, len);
        //TRACE(it _ len);
        for (int y : adj[it.first]) {
          int sub = (it.first == x) ? y : it.second;
          if (done[y]) continue;
          nvec[input[y]].push_back({y, sub});
        }
      }
      for (auto it : vec) {
        for (int y : adj[it.first]) {
          if (done[y]) continue;
          if (!ok(nvec[input[y]])) nvec[input[y]].clear();
          if (nvec[input[y]].empty()) continue;
          NV.push_back(nvec[input[y]]);
          nvec[input[y]].clear();
        }
      }
    }

    V = NV;
  }

  for (int it : history)
    done[it] = false;
  history.clear();

  return ret;
}

int main(void) {
  cin >> n;
  cin >> input;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    int w = n + i;
    adj[u].push_back(w);
    adj[v].push_back(w);
    adj[w].push_back(u);
    adj[w].push_back(v);
  }
  int ans = 1; //solve(4);
  for (int i = 0; i < 2 * n - 1; ++i) {
    ans = max(ans, solve(i));
    //TRACE(i _ solve(i));
  }
  cout << ans << endl;
  return 0;
}
