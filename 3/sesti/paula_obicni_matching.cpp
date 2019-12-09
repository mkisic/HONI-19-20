#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
  
const int MAXN = 1e6 + 10;
int match[MAXN], vis[MAXN], tick;
vector<int> e[MAXN];

bool f(int i) {
    if (i == -1) return true;
    if (vis[i] == tick) return false;
    vis[i] = tick;

    /*
    for (int j : e[i]) {
        if (f(match[j])) {
            match[j] = i;
            return true;
        }
    }
    */
    for (int j = 0; j < (int)e[i].size(); j++) {
        if (f(match[e[i][j]])) {
            match[e[i][j]] = i;
            return true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = n - k; i < n; i++)
        //for (int j = k - 1; j >= 0; j--)
        //    if ((i & j) == j) e[i].push_back(j);
        for (int j = i; ; j = (j - 1) & i) {
            if (j < k) e[i].push_back(j);
            if (j == 0) break;
        }

    for (int i = 0; i < k; i++)
        match[i] = -1;

    for (int i = n - k; i < n; i++) {
        tick++;
        assert(f(i));
    }

    for (int i = 0; i < k; i++)
        cout << i << " " << match[i] << "\n";

    return 0;
}

