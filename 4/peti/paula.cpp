#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int ALPHA = 26;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;

    int sol_cnt = 1e9, sol_l = -1, sol_r = -1;

    vector<int> pre(ALPHA, -1);
    for (int i = 0; i < n; i++) {
        pre[s[i] - 'a'] = i;

        auto v = pre;
        sort(v.rbegin(), v.rend());
        for (int j = 1; j < ALPHA; j++)
            if ((ll)j * (sol_r - sol_l + 1) < (ll)sol_cnt * (i - v[j])) {
                sol_cnt = j;
                sol_l = v[j] + 1;
                sol_r = i;
            }
    }

    cout << sol_l + 1 << " " << sol_r + 1 << "\n";

    return 0;
}

