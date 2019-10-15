#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    
    int cnt[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) cnt[s[i] - '1']++;

    if (max(cnt[0], max(cnt[1], cnt[2])) == n ||
        cnt[0] % 2 != cnt[1] % 2 ||
        cnt[0] % 2 != cnt[2] % 2)
        cout << "NE";
    else
        cout << "DA";

    return 0;
}

