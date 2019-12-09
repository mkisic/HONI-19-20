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

    set<int> S;
    for (int i = n - k; i < n; i++) S.insert(i);
    
    for (int i = k - 1; i >= 0; i--) {
        for (auto j : S)
            if ((i & j) == i) {
                S.erase(j);
                cout << i << " " << j << "\n";
                break;
            }
        assert((int)S.size() == i);
    }

    return 0;
}
