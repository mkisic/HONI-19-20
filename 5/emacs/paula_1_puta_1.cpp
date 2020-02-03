#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int sol = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
            sol += s[j] == '*';
    }

    cout << sol;

    return 0;
}

