#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 1e5 + 10;
int x[MAXN][2];
vector<int> V[MAXN][2];
bool vis[MAXN];
vector<pii> sol[2];

const int INF = 1e9;

void no() {
    cout << "NE\n";
    exit(0);
}

void find_path(int i, bool is_cycle) {
    if (vis[i]) return;

    int st_o = V[x[i][0]][0].size() != 2, o = st_o;
    while (!vis[i]) {
        vis[i] = true;
        if (V[x[i][o]][o].size() == 1) break;

        int j = V[x[i][o]][o][0] ^ V[x[i][o]][o][1] ^ i;
        pii a = {i, j};

        if (is_cycle) {
            sol[o].push_back(a);
        } else {
            if (o == st_o) {
                sol[0].push_back(a);
                sol[1].push_back(a);
            }
        }

        i = j;
        o ^= 1;
    }

    if (!is_cycle && o == st_o) no();
}

bool check(int n, vector<pii>& A) {
  vector<vector<int>> in(MAXN), out(MAXN);
  vector<vector<pii>> query(MAXN);
  for (int i = 0; i < n / 2; i++) {
      int a = A[i].fi, b = A[i].se;
      if (x[a][0] == x[b][0]) {
          int l = x[a][1], r = x[b][1];
          if (l > r) swap(l, r);
          query[x[a][0]].push_back({l, r});
      } else if (x[a][1] == x[b][1]) {
          int l = x[a][0], r = x[b][0];
          if (l > r) swap(l, r);
          in[l].push_back(x[a][1]);
          out[r].push_back(x[a][1]);
      } else {
          assert(false);
      }
  }

  set<int> S = {INF};
  for (int i = 0; i < MAXN; i++) {
      for (int a : in[i]) S.insert(a);
      for (auto p : query[i])
          if (*S.lower_bound(p.fi) <= p.se) return false;
      for (int a : out[i]) S.erase(a);
  }

  return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i][0] >> x[i][1];
        V[x[i][0]][0].push_back(i);
        V[x[i][1]][1].push_back(i);
    }

    for (int i = 0; i < MAXN; i++)
        for (int j : {0, 1})
            if (V[i][j].size() == 1)
                find_path(V[i][j][0], false);
    for (int i = 0; i < MAXN; i++)
        for (int j : {0, 1})
            if (V[i][j].size() == 2)
                find_path(V[i][j][0], true);

    if (check(n, sol[0])) {
        cout << "DA\n";
        for (auto p : sol[0]) cout << p.fi + 1 << " " << p.se + 1 << "\n";
    } else if (check(n, sol[1])) {
        cout << "DA\n";
        for (auto p : sol[1]) cout << p.fi + 1 << " " << p.se + 1 << "\n";
    } else {
        no();
    }

    return 0;
}

