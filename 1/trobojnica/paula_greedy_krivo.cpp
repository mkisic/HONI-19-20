// ovo pada na primjeru 11111...11122,
// a bez random pocetka je jos lakse rusiti, npr 12333

#include <bits/stdc++.h>
using namespace std;

const int MaxN = 2e5 + 10;
int nxt[MaxN], color[MaxN];
int sol_x[MaxN], sol_y[MaxN], sol_c[MaxN];

int main() {
    srand(time(0));

    int n;
    string s;
    cin >> n >> s;

    for (int iter = 0; iter < 10; iter++) {
        int cnt[3] = {0, 0, 0};
        for (int i = 0; i < n; i++) {
            color[i] = s[i] - '1';
            cnt[s[i] - '1']++;
            nxt[i] = (i + 1) % n;
        }

        int x = rand() % n;
        bool found_ans = true;
        for (int i = 0; i < n - 3; i++) {
            if (max(cnt[0], max(cnt[1], cnt[2])) == n - i) {
                found_ans = false;
                break;
            }

            while (color[x] == color[nxt[x]]) x = nxt[x];

            int y = nxt[x];
            int new_color = 3 - color[x] - color[y];
            cnt[color[x]]--;
            cnt[color[y]]--;
            cnt[new_color]++;
            color[x] = new_color;
            nxt[x] = nxt[y];
            sol_x[i] = x;
            sol_y[i] = nxt[y];
            sol_c[i] = new_color;
        }
        
        if (found_ans && cnt[0] == 1 && cnt[1] == 1) {
            cout << "DA\n";
            for (int i = 0; i < n - 3; i++)
                cout << sol_x[i] + 1 << " "
                     << sol_y[i] + 1 << " "
                     << sol_c[i] + 1 << "\n";
            return 0;
        }
    }

    cout << "NE\n";
    return 0;
}

