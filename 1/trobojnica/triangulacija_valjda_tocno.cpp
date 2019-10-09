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
    return edge[prev_id[i]] == edge[i] &&
        edge[i] != edge[next_id[i]];
}

int third_color(int a, int b) {
    return 1 + 2 + 3 - a - b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));

    cin >> n >> color;

    bool all_equal = true;

    for (int i = 0; i < n; i++) {
        next_id[i] = (i + 1) % n;
        prev_id[i] = (i - 1 + n) % n;
        edge[i] = color[i] - '0';
        all_equal &= color[i] == color[0];
    }

    if (all_equal) {
        cout << "NE\n";
        return 0;
    }

    int count = 0;
    for (int i = 0; i < n; i++)
        if (is_good(i)) count++;

    int i = 0;
    for (int sol_i = 0; sol_i < n - 3; sol_i++) {
        while (count > 0 && !is_good(i)) i = next_id[i];
        
        int a = prev_id[i];
        int b = next_id[i];
        int c = next_id[b];

        if (is_good(a)) count--;
        if (is_good(i)) count--;
        if (is_good(b)) count--;
        if (is_good(c)) count--;

        assert(edge[i] != edge[b]);
        int new_color = third_color(edge[i], edge[b]);
        edge[i] = new_color;
        next_id[i] = c;
        prev_id[c] = i;

        if (is_good(a)) count++;
        if (is_good(i)) count++;
        if (is_good(c)) count++;

        sol[sol_i][0] = i;
        sol[sol_i][1] = c;
        sol[sol_i][2] = new_color;

        i = prev_id[i];
    }

    if (count == 0) {
        cout << "DA\n";
        for (int i = 0; i < n - 3; i++)
            cout << sol[i][0] + 1 << " "
                 << sol[i][1] + 1 << " "
                 << sol[i][2] << "\n";
    } else {
        cout << "NE\n";
    }

    return 0;
}

