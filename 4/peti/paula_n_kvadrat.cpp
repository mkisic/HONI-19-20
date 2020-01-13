#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long ll;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;

    int sol_cnt = 1e9, sol_l = -1, sol_r = -1;

    for (int i = 0; i < n; i++) {
        bool in[26];
        for (int j = 0; j < 26; j++) in[j] = false;
        int cnt = 0;

        for (int j = i; j < n; j++) {
            if (!in[s[j] - 'a']) {
                in[s[j] - 'a'] = true;
                cnt++;
            }
            
            if ((ll)cnt * (sol_r - sol_l + 1) < (ll)sol_cnt * (j - i + 1)) {
                sol_cnt = cnt;
                sol_l = i;
                sol_r = j;
            }
        }
    }

    cout << sol_l + 1 << " " << sol_r + 1 << "\n";

    return 0;
}

