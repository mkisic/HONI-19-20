#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100100;
const int BASE = 31337;

int n;
char s[MAXN];
vector<int> adj[MAXN];


int rec(int x, int prev = -1, ll hdown = 0, ll hup = 0, ll p = 1, int len = 1) {
  hdown = hdown * BASE + s[x];
  hup = hup + p * s[x];
  int ret = 0;
  if (hup == hdown) ret = len;
  for (int y : adj[x]) {
    if (y == prev) continue;
    ret = max(ret, rec(y, x, hdown, hup, p * BASE, len + 1));
  }
  return ret;
}

int main(void) {
  cin >> n;
  cin >> s;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int ans = 0;
  for (int i = 0; i < n; ++i)
    ans = max(ans, rec(i));
  cout << ans << endl;
  return 0;
}
