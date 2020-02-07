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
vector<vector<pii>> C[2];
vector<pii> Q[2];

void no() {
    cout << "NE\n";
    exit(0);
}

void find_path(int i, bool is_cycle) {
    if (vis[i]) return;

    if (is_cycle) {
        C[0].push_back(vector<pii>());
        C[1].push_back(vector<pii>());
    }

    int st_o = V[x[i][0]][0].size() != 2, o = st_o;
    while (!vis[i]) {
        vis[i] = true;
        if (V[x[i][o]][o].size() == 1) break;

        int j = V[x[i][o]][o][0] ^ V[x[i][o]][o][1] ^ i;

        if (is_cycle) {
            C[o].back().push_back({i, j});
        } else {
            if (o == st_o)
                Q[o].push_back({i, j});
        }

        i = j;
        o ^= 1;
    }

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

    for (pii& a : Q[0])
        for (pii& b : Q[1])
            if (intersect(a, b, 0)) no();

    int k = (int)C[0].size();
    for (int mask = 0; mask < (1 << k); mask++) {
        bool ok = true;
        for (int i = 0; i < k && ok; i++) {
            if ((1 << i) & mask) continue;

            for (pii& a : C[0][i])
                for (pii& b : Q[1])
                    ok &= !intersect(a, b, 0);
            if (!ok) break;

            for (int j = 0; j < k && ok; j++) {
                if (!((1 << j) & mask)) continue;
                for (pii& a : C[0][i])
                    for (pii& b : C[1][j])
                        ok &= !intersect(a, b, 0);
            }
        }
        if (!ok) continue;

        cout << "DA\n";
        for (int o : {0, 1}) for (pii& a : Q[o])
            cout << a.fi + 1 << " " << a.se + 1 << "\n";
        for (int i = 0; i < k; i++) for (pii& a : C[(mask >> i) & 1][i])
            cout << a.fi + 1 << " " << a.se + 1 << "\n";
        return 0;
    }

    no();

    return 0;
}

