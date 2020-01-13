#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

const int ALPHA = 26;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;

    int sol_cnt = ALPHA, sol_l = -1, sol_r = -1;
    vector<int> L, R;

    for (int i = 0; i < n; i++) {
        bool in[ALPHA];
        for (int j = 0; j < ALPHA; j++) in[j] = false;
        int cnt = 0;

        for (int j = i; j < n; j++) {
            if (!in[s[j] - 'a']) {
                in[s[j] - 'a'] = true;
                cnt++;
            }
            
            if (cnt * (sol_r - sol_l + 1) < sol_cnt * (j - i + 1)) {
                sol_cnt = cnt;
                sol_l = i;
                sol_r = j;
                
                L.clear();
                R.clear();
            }
            if (cnt * (sol_r - sol_l + 1) == sol_cnt * (j - i + 1)) {
                L.push_back(i);
                R.push_back(j);
            }
        }
    }

    cout << sol_l + 1 << " " << sol_r + 1 << "\n";

    for (int i = 0; i < (int)L.size(); i++) {
        TRACE(L[i] _ R[i] _ s.substr(L[i], R[i] - L[i] + 1));
    }

    return 0;
}

