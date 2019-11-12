#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

const string JA = "NijeZivotJedanACM";
const int MAXN = 1010;

int n, m;

vector <pair <pii, string> > v;
string ime;
char c;

int read_att() {
  int ret = 0;
  while (scanf("%c",&c) && c != '/' && c != ' ' && c != '\n') {
    ret *= 10;
    ret += c - '0';
  }
  return ret;
}

vector <int> moji;

pii read_tim() {
  pii ret;
  int last = 1;
  REP(j, m) {
    if (last) scanf("%c",&c);
    char verdict;
    scanf("%c",&verdict);
    int tries = read_att();
    if (verdict != '-') {
      int H, M, S;
      scanf("%d:%d:%d",&H,&M,&S);
      ret.fi--;
      ret.sec += S + M * 60 + H * 60 * 60 + 20 * 60 * tries;
      last = 1;
      if (ime == JA) moji.pb(S + M * 60 + H * 60 * 60 + 20 * 60 * tries);
    } else {
      if (ime == JA) moji.pb(0);
      last = 0;
    }
  }
  return ret;
}

pii zadnji() {
  pii ret = {0, 0};
  int pt = 0;
  while (scanf("%c",&c) != EOF) {
    if (c == '+') {
      ret.fi--;
      ret.sec += moji[pt++];
    } else if (c == '-') pt++;
  }
  return ret;
}

int main() {
  scanf("%d %d",&n,&m);
  REP(i, n) {
    cin >> ime;
    pii t = read_tim();
    if (ime != JA) v.pb({t, ime});
  }
  sort(all(v));
  cin >> ime;
  pair <pii, string> mi = {zadnji(), JA};
  REP(i, (int)v.size()) {
    if (v[i] > mi) {
      printf("%d\n",i + 1);
      return 0;
    }
  }
  printf("%d\n",n);
  return 0;
}
