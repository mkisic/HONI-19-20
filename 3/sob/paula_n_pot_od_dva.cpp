#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    int a = 0, b = n - k;
    for (int i = 19; i >= 0; i--) {
        if (!((1 << i) & k)) continue;
        for (int x = b; x < b + (1 << i); x++)
            cout << a + (x & ((1 << i) - 1)) << " " << x << "\n";
        a += (1 << i);
        b += (1 << i);
    }

    return 0;
}

