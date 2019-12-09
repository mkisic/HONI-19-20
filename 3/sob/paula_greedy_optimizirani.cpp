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

    int lo = n - k;
    for (int i = k - 1; i >= 0; ) {
        int hi = lo;
        while ((hi & i) != i) hi++;
        for (int j = hi; j >= lo; j--)
            cout << i-- << " " << j << "\n";
        lo = hi + 1;
    }

    return 0;
}

