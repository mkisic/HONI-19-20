#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
string t[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> t[i];

    int sol = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sol += (i == 0 || t[i - 1][j] == '.') &&
                   (j == 0 || t[i][j - 1] == '.') &&
                   t[i][j] == '*';

    cout << sol << "\n";

    return 0;
}

