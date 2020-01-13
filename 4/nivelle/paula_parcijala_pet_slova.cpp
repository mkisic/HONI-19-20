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

const int ALPHA = 5;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;

    int sol_cnt = ALPHA, sol_l = -1, sol_r = -1;

    for (int mask = 1; mask < (1 << ALPHA); mask++) {
        int l = -1, r = -1;
        for (int i = 0; i < n; ) {
            if (!((1 << (s[i] - 'a')) & mask)) {
                i++;
                continue;
            }

            int j = i;
            while (j < n && (1 << (s[j] - 'a')) & mask) j++;
            if (j - i > r - l + 1) {
                l = i;
                r = j - 1;
            }
            i = j;
        }

        int cnt = __builtin_popcount(mask);
        if (cnt * (sol_r - sol_l + 1) < sol_cnt * (r - l + 1)) {
            sol_cnt = cnt;
            sol_l = l;
            sol_r = r;
        }
    }

    cout << sol_l + 1 << " " << sol_r + 1 << "\n";

    return 0;
}

