#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<
#define pb push_back
#define fi first
#define se second
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define TRACE(x) cerr << #x << "  " << x << endl
template<typename T1, typename T2>inline void minaj(T1 &x, T2 y) { x = (x > y ? y: x);}
template<typename T1, typename T2>inline void maxaj(T1 &x, T2 y) { x = (x < y ? y: x);}

typedef pair<int, int> pii;

struct node {
  set<int> s;
  node *l, *r;
  node() {}
  node(node *x, node *y) {
    l = x;
    r = y;
  }
};

node *trie;

const int MAXN = 1e6 + 5;
vector<int> e[MAXN];
vector<pii> events;

int d[MAXN];
int lo[MAXN], hi[MAXN], cookie;

void dfs(int x, int y) {
  lo[y] = cookie ++;
  for(auto z: e[y]) {
    if(z != x) {
      d[z] ^= d[y];
      dfs(y, z);
    }
  }
  hi[y] = cookie;
}

bool ima(node *T, int x) {
  if(T == NULL) return false;
  auto it = T->s.lower_bound(lo[x]);
  if(it != T->s.end() && (*it) < hi[x]) return true;
  return false;
}

const int MAX = 30;

int search(int x, int y) {
  int ret = 0;
  node *tmp = trie;
  for(int i = MAX; i >= 0; --i) {
    node *zelim, *moram;

    zelim = tmp->r;
    moram = tmp->l;

    if((1 << i) & d[x]) {
      swap(zelim, moram);
    }
    if(ima(zelim, y)) {
      tmp = zelim;
      ret += (1 << i);
    } else {
      tmp = moram;
    }
  }
  return ret;
}

void dodaj(int x) {
  node *tmp = trie;
  for(int i = MAX; i >= 0; --i) {
    if((1 << i) & d[x]) {
      if(!(tmp->r)) tmp->r = new node(NULL, NULL);
      tmp = tmp->r;
    } else {
      if(!(tmp->l)) tmp->l = new node(NULL, NULL);
      tmp = tmp->l;
    }
    tmp->s.insert(lo[x]);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  trie = new node(NULL, NULL);

  int q; cin >> q;
  int n = 1;
  REP(i, q) {
    string s; cin >> s;
    if(s[0] == 'A') {
      int x, y; cin >> x >> y;
      d[++n] = y;
      e[n].pb(x);
      e[x].pb(n);
      events.pb({-1, n});
    } else {
      int x, y; cin >> y >> x;
      events.pb({x, y});
    }
  }

  dfs(1, 1);
  dodaj(1);
  REP(i, q) {
    int x = events[i].second;
    int y = events[i].first;

    if(events[i].first == -1) {
      dodaj(x);
    } else {
      cout << search(x, y) << '\n';
    }
  }
}
