#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

const string CORRECT = "tocno";
const string WRONG_TRIANGULATION = "neispravna triangulacija";
const string WRONG_COLORING = "neispravno bojenje";

const int MAXN = 2e5 + 10;

int n;
pii nxt[MAXN];

int dist(int a, int b) {
    return (b + n - a) % n;
}

bool check_triangle(int a, int b, int c) {
    return a + b + c == 6 && a != b;
}

bool check_triangle(int a) {
    int b = nxt[a].fi;
    int c = nxt[b].fi;
    if (nxt[c].fi != a) return false;
    return check_triangle(nxt[a].se, nxt[b].se, nxt[c].se);
}

bool solve(vector<pair<pii, int>> diagonals) {
    auto chosen_d = diagonals[rand() % diagonals.size()];
    int a = chosen_d.fi.fi;
    int b = chosen_d.fi.se;
    if (a > b) swap(a, b);

    vector<pair<pii, int>> new_diagonals[2];
    for (auto other_d : diagonals) {
        if (other_d == chosen_d) continue;

        int c = other_d.fi.fi;
        int d = other_d.fi.se;

        if (dist(a, c) + dist(c, d) + dist(d, b) == dist(a, b) ||
            dist(a, d) + dist(d, c) + dist(c, b) == dist(a, b)) {
            new_diagonals[0].push_back(other_d);
        } else if (dist(b, c) + dist(c, d) + dist(d, a) == dist(b, a) ||
                 dist(b, d) + dist(d, c) + dist(c, a) == dist(b, a)) {
            new_diagonals[1].push_back(other_d);
        } else {
            cout << WRONG_TRIANGULATION << "\n";
            exit(0);
        }
    }

    auto tmp_a = nxt[a], tmp_b = nxt[b];
    for (int i : {0, 1}) {
        if (i == 0) {
            nxt[b] = {a, chosen_d.se};
        } else {
            nxt[b] = tmp_b;
            nxt[a] = {b, chosen_d.se};
        }

        if (new_diagonals[i].size() == 0) {
            if (!check_triangle(a)) return false;
        } else {
            if (!solve(new_diagonals[i])) return false;
        }
    }
    nxt[a] = tmp_a;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));

    int t;
    cin >> t;

    cin >> n;
    string colors;
    cin >> colors;
    for (int i = 0; i < n; i++) {
        nxt[i] = {(i + 1) % n, colors[i] - '0'};
    }

    vector<pair<pii, int>> diagonals;
    for (int i = 0; i < n - 3; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;

        diagonals.push_back({{a, b}, c});
    }

    if (!solve(diagonals)) {
        cout << WRONG_COLORING << "\n";
    } else {
        cout << CORRECT << "\n";
    }

    return 0;
}

