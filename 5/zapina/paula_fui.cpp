#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

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
int n, choose[MAXN][MAXN];

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

    int sol = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int sum = 0, k = __builtin_popcount(mask);
        for (int i = 0; i < n; i++) if ((1 << i) & mask) sum += i + 1;
        if (sum > n) continue;
        int tmp = 1, tot = n;
        for (int i = 0; i < n; i++)
            if ((1 << i) & mask) {
                tmp = mul(tmp, choose[tot][i + 1]);
                tot -= i + 1;
            }
        tmp = mul(tmp, pow(n - k, tot));
        if (!(k & 1)) tmp = MOD - tmp;
        sol = add(sol, tmp);
    }

    cout << sol << "\n";

    return 0;
}

