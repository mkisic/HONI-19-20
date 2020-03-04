#include <bits/stdc++.h>
using namespace std;

const int maxm = 10;
const int maxn = 505;
const int inf = 1e9;
int max_mask;
int N, M;
int dp[maxn][(1 << maxm)];
int prijelaz[maxn][(1 << maxm)];
int space[maxn][maxm];
int sol = inf;
int mask_sol;
vector <int> v[maxn][(1 << maxm)];
string s[maxn];

int get_val(int x, int line)
{
    int val = 0;
        for (int k = 1; k <= M; k++)
            if (s[line][k] == '0') 
                val += ((1 << (k - 1)) & x);
    return val;
}

int get_plus(int x, int line)
{
    int plus = 0;
    for (int k = 1; k < M; k++)
         if (s[line][k] == '1')
             if (((1 << (k - 1)) & x) == (1 << (k - 1)))                        
                plus++;
    return plus;
}

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> s[i];
}

void solve()
{
    max_mask = (1 << (M - 1));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < max_mask; j++)
            dp[i][j] = prijelaz[i][j] = inf;
    for (int i = 0; i < max_mask; i++)
        dp[0][i] = __builtin_popcount(i);
    for (int i = 1; i < N; i++)
    {
        int cnt = -1;
        for (int j = M - 1; j >= 0; j--)
        {
            cnt++;
            if (s[i][j] == '1') {space[i][j] = cnt; cnt = -1;}
        }
    }
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (s[i][j] == '1')
            {
                int control = 0;
                for (int k = j + 1; k <= j + space[i][j]; k++)
                    control |= (1 << (k - 1));
                for (int k = 0; k < max_mask; k++)
                    if ((k & control) != control) 
                        {dp[i - 1][k]++; v[i - 1][k].push_back(j + 1);}
            }
        }
        for (int j = 0; j < max_mask; j++)
        {
            int val = get_val(j, i);
            prijelaz[i][val] = min(prijelaz[i][val], dp[i - 1][j]);
        }

        for (int j = 0; j < max_mask; j++)
        {
            int val = get_val(j, i);
            dp[i][j] = prijelaz[i][val] + get_plus(j, i);
        }
    }

    for (int i = 0; i < max_mask; i++) 
    {
        if (dp[N - 1][i] < sol)
        {
            sol = dp[N - 1][i];
            mask_sol = i;
        }
    }

    cout << sol << '\n';
}

void reconstruct()
{
    int last_mask_sol = mask_sol;
    int line = N - 1;
    int minx = 1e9;
    int const_val;

    while (line >= 0)
    {
        for (int i = 1; i < M; i++)
        {
            if (s[line][i] == '1')
                if ((mask_sol & (1 << (i - 1))) == (1 << (i - 1)))
                    cout << line + 1 << ' ' << i + 1 << " DOLJE\n";
        }
        for (int i = 0; i < v[line][mask_sol].size(); i++)
            cout << line + 2 << ' ' << v[line][mask_sol][i] << " DESNO\n";

        if (line > 0)
        {
            const_val = get_val(mask_sol, line);
            last_mask_sol = mask_sol;

            for (int i = 0; i < max_mask; i++)
            {
                if (get_val(i, line) == const_val)
                    if (dp[line - 1][i] < minx)
                        {minx = dp[line - 1][i]; mask_sol = i;}
            }
        }

        line--;
    }

    return;
}

int main()
{
    input();
    solve();
    reconstruct();
}
