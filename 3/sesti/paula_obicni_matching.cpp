#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
  
const int MAXN = (1 << 20) + 10;
int match[MAXN], vis[MAXN], tick;
vector<int> e[MAXN];

bool f(int i) {
    if (i == -1) return true;
    if (vis[i] == tick) return false;
    vis[i] = tick;

    for (int j : e[i]) {
        if (f(match[j])) {
            match[j] = i;
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

    for (int i = 0; i < k; i++)
        for (int j = n - k; j < n; j++)
            if ((i & j) == i) e[i].push_back(j);
    for (int j = n - k; j < n; j++)
        match[j] = -1;

    for (int i = 0; i < k; i++) {
        tick++;
        assert(f(i));
    }

    for (int j = n - k; j < n; j++)
        cout << match[j] << " " << j << "\n";

    return 0;
}

