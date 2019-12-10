#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i < (int) (b); ++i)
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

typedef double lf;
typedef long long ll;
typedef pair<int, int> pii;

const int mod = 1e9 + 7;
int add(int x, int y) {x += y; if(x >= mod) return x - mod; return x;}
int sub(int x, int y) {x -= y; if(x < 0) return x + mod; return x;}
int mul(int x, int y) {return (ll) x * y % mod;}

bool check(vector<int> v) {
  if(v.size() == 1) return true;
  if(v.size() == 0) return false;

  int d = v[1] - v[0];
  FOR(i, 2, v.size()) {
    if(v[i] != v[i - 1] + d) {
      return false;
    }
  }
  return true;
}

#define unique uni

map<int, int> cnt;
map<int, int> diff;

void print(vector<int> v) {
  cout << v.size() << endl;
  for(int x: v) {
    cout << x << " ";
  }
  cout << endl;
}
void print(multiset<int> v) {
  cout << v.size() << endl;
  for(int x: v) {
    cout << x << " ";
  }
  cout << endl;
}

void makni(int x, int y, int &unique) {
  if(diff[y - x] == 1) unique --;
  diff[y - x] --;
}
void dodaj(int x, int y, int &unique) {
  if(diff[y - x] == 0) unique ++;
  diff[y - x] ++;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;

  vector<int> v;
  v.resize(n);
  REP(i, n) {
    cin >> v[i];
  }
  sort(all(v));

  if(n == 2) {
    cout << 1 << endl;
    cout << v[0] << endl;
    cout << 1 << endl;
    cout << v[1] << endl;
    cout << endl;
    return 0;
  }

  for(pii p: {pii(v[0], v[1]), pii(v[0], v[2]), pii(v[1], v[2])}) {

    for(int h: v) {
      cnt[h] = 0;
    }
    for(int h: v) {
      cnt[h] ++;
    }

    int a = p.fi;
    int d = p.se - p.fi;

    diff.clear();

    vector<int> prvi;
    multiset<int> drugi;

    int unique = 0;
    REP(i, n) {
      if(i) {
        diff[v[i] - v[i - 1]] ++;
        if(diff[v[i] - v[i - 1]] == 1) {
          unique ++;
        }
      }
      drugi.insert(v[i]);
    }

    while(cnt[a]) {
      auto it = drugi.find(a);
      auto it_pre = it;
      auto it_post = it;

      it_pre --;
      it_post ++;

      if(it_post != drugi.end()) {
        makni(*it, *it_post, unique);
      }
      if(it != drugi.begin()) {
        makni(*it_pre, *it, unique);
      }
      if(it != drugi.begin() && it_post != drugi.end()) {
        dodaj(*it_pre, *it_post, unique);
      }

      drugi.erase(it);
      prvi.pb(a);
      a += d;

      if(unique == 1 || drugi.size() == 1) {
        print(prvi);
        print(drugi);
        return 0;
      }
    }
  }
  cout << -1 << endl;
}
