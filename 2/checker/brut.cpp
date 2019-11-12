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

    int n;
    cin >> n;
    string colors;
    cin >> colors;
    vector<pair<pii, int>> diagonals;
    for (int i = 0; i < n; i++) {
        pii p;
        if (i == n - 1) p = {0, n - 1};
        else p = {i, i + 1};
        diagonals.push_back({p, colors[i] - '0'});
    }

    for (int i = 0; i < n - 3; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        if (a > b) swap(a, b);
        diagonals.push_back({{a, b}, c});
    }

    for (int i = 0; i < (int)diagonals.size(); i++) {
        for (int j = i + 1; j < (int)diagonals.size(); j++) {
            auto p = diagonals[i].fi, q = diagonals[j].fi;
            int cnt = 0;
            for (int x = p.fi; x != p.se; x = (x + 1) % n)
                if (x == q.fi || x == q.se) cnt++;
            set<int> s = {p.fi, p.se, q.fi, q.se};

            if ((cnt == 1 && s.size() == 4) || p == q) {
                cout << WRONG_TRIANGULATION << "\n";
                return 0;
            }
        }
    }

    for (int i = 0; i < (int)diagonals.size(); i++) {
        for (int j = i + 1; j < (int)diagonals.size(); j++) {
            for (int k = j + 1; k < (int)diagonals.size(); k++) {
                auto p = diagonals[i];
                auto q = diagonals[j];
                auto r = diagonals[k];

                set<int> s = {p.fi.fi, p.fi.se, q.fi.fi,
                    q.fi.se, r.fi.fi, r.fi.se};
                if (s.size() == 3 && !check_triangle(p.se, q.se, r.se)) {
                    cout << WRONG_COLORING << "\n";
                    return 0;
                }
            }
        }
    }

    cout << CORRECT << "\n";

    return 0;
}

