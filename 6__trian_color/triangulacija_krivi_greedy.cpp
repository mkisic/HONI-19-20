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

bool is_good(int i) {
    return edge[i] != edge[next_id[i]];
}

void try_to_solve() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        next_id[i] = (i + 1) % n;
        prev_id[i] = (i - 1 + n) % n;
        edge[i] = color[i] - '0';

        if (color[i] != color[(i + 1) % n]) count++;
    }

    int b = rand() % n;
    for (int i = 0; i < n - 3; i++) {
        if (count == 0) return;

        while (!is_good(b)) b = next_id[b];

        int a = prev_id[b];
        int c = next_id[b];
        int d = next_id[c];
        int new_color = 1 + 2 + 3 - edge[b] - edge[c];

        if (is_good(a)) count--;
        if (is_good(b)) count--;
        if (is_good(c)) count--;

        next_id[b] = d;
        prev_id[d] = b;
        edge[b] = new_color;

        if (is_good(a)) count++;
        if (is_good(b)) count++;

        sol[i][0] = b;
        sol[i][1] = d;
        sol[i][2] = new_color;

        b = prev_id[b];
    }

    if (count < 3) return;

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

    for (int i = 0; i < 100; i++)
        try_to_solve();

    cout << "NE\n";

    return 0;
}

