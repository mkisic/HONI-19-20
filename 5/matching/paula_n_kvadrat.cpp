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
int cycle_id[MAXN];
vector<vector<int>> cycle;
queue<pii> Q[2];
vector<pii> M[2];
set<pii> P[2];

void no() {
    cout << "NE\n";
    exit(0);
}

void find_path(int i, bool is_cycle) {
    if (vis[i]) return;

    if (is_cycle) cycle.push_back(vector<int>());

    int st_o = V[x[i][0]][0].size() != 2, o = st_o;
    while (!vis[i]) {
        vis[i] = true;
        if (V[x[i][o]][o].size() == 1) break;

        int j = V[x[i][o]][o][0] ^ V[x[i][o]][o][1] ^ i;

        if (is_cycle) {
            cycle.back().push_back(i);
            cycle_id[i] = (int)cycle.size() - 1;
            P[o].insert({i, j});
        } else {
            if (o == st_o)
                Q[o].push({i, j});
        }

        i = j;
        o ^= 1;
    }

    if (is_cycle) cycle.back().push_back(i);
    if (!is_cycle && o == st_o) no();
}

bool intersect(pii& a, pii& b, int o) {
    int la = x[a.fi][o ^ 1], ra = x[a.se][o ^ 1], ma = x[b.fi][o ^ 1];
    if (la > ra) swap(la, ra);
    int lb = x[b.fi][o], rb = x[b.se][o], mb = x[a.fi][o];
    if (lb > rb) swap(lb, rb);
    return (la <= ma && ma <= ra) && (lb <= mb && mb <= rb);
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

    vector<bool> matched_cycle(cycle.size(), false);
    
    vector<pii> sol;
    while (!(Q[0].empty() && Q[1].empty())) {
        int o = Q[0].empty();
        int i = Q[o].front().fi, j = Q[o].front().se;
        pii& a = Q[o].front();
        Q[o].pop();

        int l = x[i][o ^ 1], r = x[j][o ^ 1];
        if (l > r) swap(l, r);

        for (pii& b : M[o ^ 1]) if (intersect(a, b, o)) no();

        set<int> intersect_cycles;
        for (pii b : P[o ^ 1])
            if (intersect(a, b, o)) intersect_cycles.insert(cycle_id[b.fi]);

        for (int c : intersect_cycles) {
            matched_cycle[c] = true;
            for (int k = 0; k < (int)cycle[c].size() - 1; k++) {
                int oc = k & 1, ic = cycle[c][k], jc = cycle[c][k + 1];
                P[oc].erase({ic, jc});
                if (oc == o) Q[oc].push({ic, jc});
            }
        }

        M[o].push_back(a);
        sol.push_back(a);
    }

    for (int i = 0; i < (int)cycle.size(); i++)
        if (!matched_cycle[i])
            for (int j = 0; j < (int)cycle[i].size() - 1; j += 2)
                sol.push_back({cycle[i][j], cycle[i][j + 1]});

    cout << "DA\n";
    for (auto p : sol) cout << p.fi + 1 << " " << p.se + 1 << "\n";

    return 0;
}

