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
map<int, int> diagonals[MAXN];

int dist(int a, int b) {
    return (b + n - a) % n;
}

bool check_triangle(int a, int b, int c) {
    return a + b + c == 6 && a != b;
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

    for (int i = 0; i < n - 3; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;

        diagonals[a][b] = c;
        diagonals[b][a] = c;
    }

    bool coloring = true;
    int a = rand() % n;
    for (int i = 0; i < n - 2; i++) {
        int start_a = a;
        while (!diagonals[a].count(nxt[nxt[a].fi].fi)) {
            a = nxt[a].fi;
            if (a == start_a) {
                cout << WRONG_TRIANGULATION << "\n";
                return 0;
            }
        }

        int b = nxt[a].fi;
        int c = nxt[b].fi;

        coloring &= check_triangle(nxt[a].se, nxt[b].se, diagonals[a][c]);

        nxt[a] = {c, diagonals[a][c]};
        diagonals[a].erase(c);
    }

    if (!coloring) {
        cout << WRONG_COLORING << "\n";
    } else {
        cout << CORRECT << "\n";
    }

    return 0;
}

