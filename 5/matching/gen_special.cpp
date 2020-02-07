#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
  
const int MAXN = 1e5;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    assert(argc == 4);
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int cuts = atoi(argv[3]);
    
    vector<int> x(MAXN), y(MAXN);
    for (int i = 0; i < MAXN; i++)
        x[i] = y[i] = i + 1;
    shuffle(x.begin(), x.end(), rng);
    shuffle(y.begin(), y.end(), rng);
    sort(x.begin(), x.begin() + n + 5);
    sort(y.begin(), y.begin() + n + 5);

    n /= 4;
    int m = n / k;
    n = m * k;

    vector<pii> points;
    for (int i = 0; i < m; i++) {
        vector<int> a(k), b(k);
        for (int j = 0; j < k; j++) {
            a[j] = 1 + i * 2 * k + j;
            b[j] = a[j] + k;
        }
        a[0]--; b.back()++;

        for (int j = 0; j < k; j++) {
            for (int u : {a[j], b[j]})
                for (int v : {a[j], b[j]})
                    points.push_back(make_pair(x[u], y[v]));
        }
    }

    assert((int)points.size() == n * 4);
    
    if (cuts) {
        points.erase(points.begin(), points.begin() + 2);
        if (cuts == 2) {
            points.erase(points.end() - 1);
            points.erase(points.end() - 2);
        }
    }

    shuffle(points.begin(), points.end(), rng);
    assert((int)points.size() <= MAXN);
    cout << points.size() << "\n";
    for (pii& p : points) {
        assert(1 <= p.fi && p.fi <= MAXN);
        assert(1 <= p.se && p.se <= MAXN);
        cout << p.fi << " " << p.se << "\n";
    }

    return 0;
}

