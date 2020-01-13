#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e2 + 5;
const int maxk = 1e4 + 5;
int N, K;
int L, R;
int a[maxn];
int suma;
int sol;
int dpL[maxn][maxn][maxk];
int dpR[maxn][maxn][maxk];

int main()
{
    cin >> N >> L >> R >> K;
    for (int i = 1; i <= N; i++)
        cin >> a[i];
    for (int i = L; i <= R; i++)
        suma += a[i];
    for (int i = L; i <= R; i++)
    {
        for (int j = L - 1; j > 0; j--)
        {
            for (int k = 0; k <= K; k++)
            {
                dpL[i][j][k] = max(dpL[i][j][k], dpL[i - 1][j][k]);
                dpL[i][j][k] = max(dpL[i][j][k], dpL[i][j + 1][k]);
                int cijena  = i - j;
                if (k >= cijena) dpL[i][j][k] = max(dpL[i][j][k], dpL[i - 1][j + 1][k - cijena] + a[i] - a[j]);
            }
        }
    }
    for (int i = R; i >= L; i--)
    {
        for (int j = R + 1; j <= N; j++)
        {
            for (int k = 0; k <= K; k++)
            {
                dpR[i][j][k] = max(dpR[i][j][k], dpR[i + 1][j][k]);
                dpR[i][j][k] = max(dpR[i][j][k], dpR[i][j - 1][k]);
                int cijena = j - i;
                if (k >= cijena) dpR[i][j][k] = max(dpR[i][j][k], dpR[i + 1][j - 1][k - cijena] + a[i] - a[j]);
            }
        }
    }

    for (int i = L - 1; i <= R; i++)
        for (int j = 0; j <= K; j++)
            sol = max(sol, dpL[i][1][j] + dpR[i + 1][N][K - j]);

    cout << suma - sol << '\n';
}
