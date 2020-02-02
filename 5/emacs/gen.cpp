#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 1000;
char t[MAXN][MAXN];
  
int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(getpid());

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int k = atoi(argv[3]);
    int f = atoi(argv[4]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            t[i][j] = '.';

    for (int x = 0; x < k; x++) {
        int a = rand() % n, b = rand() % n, c = rand() % m, d = rand() % m;
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        if (f == 1) {
            b = a;
            d = c;
        }
        if (f == 2) {
            a = 0;
            b = n - 1;
            c = 0;
            d = m - 1;
        }

        bool ok = true;
        for (int i = max(0, a - 1); i <= min(n - 1, b + 1); i++)
            for (int j = max(0, c - 1); j <= min(m - 1, d + 1); j++)
                ok &= t[i][j] == '.';
        if (!ok) continue;
        
        for (int i = a; i <= b; i++)
            for (int j = c; j <= d; j++)
                t[i][j] = '*';
    }

    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << t[i][j];
        cout << "\n";
    }

    return 0;
}

