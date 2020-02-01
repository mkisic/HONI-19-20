#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return (ll)a * b % MOD; }
int pow(int a, int b) {
    int r = 1;
    for (; b; b >>= 1) {
        if (b & 1) r = mul(r, a);
        a = mul(a, a);
    }
    return r;
}
  
const int MAXN = 510;
int n, dp[MAXN][MAXN], choose[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    choose[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        choose[i][0] = 1;
        for (int j = 1; j <= n; j++)
            choose[i][j] = add(choose[i - 1][j], choose[i - 1][j - 1]);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n; j++) 
            for (int k = 0; k <= j; k++) {
                if (k == i)
                    dp[i][j] = add(dp[i][j], mul(choose[j][k], pow(i - 1, j - k)));
                else 
                    dp[i][j] = add(dp[i][j], mul(choose[j][k], dp[i - 1][j - k]));
            }

    cout << dp[n][n];

    return 0;
}

