#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<
typedef std::pair<int, int> pii;
using namespace std;

const string CORRECT = "tocno";
const string WRONG_TRIANGULATION = "neispravna triangulacija";
const string WRONG_COLORING = "neispravno bojenje";

const int MaxN = 200200;

bool valid_triangle(int a, int b, int c) { return (a + b + c == 6) && (a != b);}

int N;
vector<pii> adj[MaxN];
vector<pii> edge[MaxN];
map<pii, int> M;

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
            int c = M[{u, v}];
            assert(c != 0);

            if (!valid_triangle(a, b, c)) return false;
        }
    }

    return true;
}

void finish(string s) {
    cout << s;
    exit(0);
}

int main() {
    int t;
    cin >> t;

    string color_str;
    cin >> N >> color_str;

    FOR(i, 1, N+1) {
        int color = color_str[i-1] - '0';
        int j = i%N + 1; 
        edge[i].push_back({j, color});
        edge[j].push_back({i, color});
        M[{min(i, j), max(i, j)}] = color;
    }

    set<pii> diagonals;
    REP(i, N-3) {
        int u, v, color;
        cin >> u >> v >> color;
        if (u > v) swap(u, v);
        if (v - u <= 1 || (v == N && u == 1))
            finish(WRONG_TRIANGULATION);
        pii diag = {u, v};
        if (diagonals.find(diag) != diagonals.end())
            finish(WRONG_TRIANGULATION);
        diagonals.insert(diag);

        adj[u].push_back({v, color});
        edge[u].push_back({v, color});
        edge[v].push_back({u, color});
        M[{u, v}] = color;
    }

    if (!check_triangulation()) finish(WRONG_TRIANGULATION);
    if (!check_colors()) finish(WRONG_COLORING);

    finish(CORRECT);
    
    return 0;
}
