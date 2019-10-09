#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<
 
typedef long long ll;
typedef long double ld;

const int MaxN = 1e6;

int n, next_id[MaxN], prev_id[MaxN], edge[MaxN];
string color;
int sol[MaxN][3];

void try_to_solve() {
    set<int> candidates;
    for (int i = 0; i < n; i++) {
        next_id[i] = (i + 1) % n;
        prev_id[i] = (i - 1 + n) % n;
        edge[i] = color[i] - '0';
        
        if (color[i] != color[(i + 1) % n]) candidates.insert(i);
    }

    for (int i = 0; i < n - 3; i++) {
        if (candidates.empty()) return;
        
        int a, b, c, d;
        auto it = candidates.lower_bound(rand() % n);
        if (it != candidates.end()) a = *it;
        else a = *candidates.begin();
        b = next_id[a];
        c = next_id[b];
        d = prev_id[a];
        assert(edge[a] != edge[b]);

        candidates.erase(d);
        candidates.erase(a);
        candidates.erase(b);
        
        int new_color = 1 + 2 + 3 - edge[a] - edge[b];
        next_id[a] = c;
        edge[a] = new_color;
        if (new_color != edge[c]) candidates.insert(a);
        prev_id[c] = a;
        if (edge[d] != new_color) candidates.insert(d);

        sol[i][0] = a;
        sol[i][1] = c;
        sol[i][2] = new_color;
    }

    if (candidates.size() < 3) return;

    cout << "DA\n";
    for (int i = 0; i < n - 3; i++)
        cout << sol[i][0] + 1 << " " << sol[i][1] + 1 << " " << sol[i][2] << "\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));

    cin >> n >> color;

    for (int i = 0; i < 10; i++)
        try_to_solve();

    cout << "NE\n";

    return 0;
}

