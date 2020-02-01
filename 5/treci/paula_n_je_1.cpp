#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    
    int sol = 0;
    for (int i = 0; i < m; i++)
        sol += (i == 0 || s[i - 1] == '.') && s[i] == '*';
    
    cout << sol;

    return 0;
}

