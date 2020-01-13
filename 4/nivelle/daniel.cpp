#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<
#define debug(...) fprintf(stderr, __VA_ARGS__)
typedef long long ll;
typedef std::pair<int, int> pii;
#define X first
#define Y second
#define double long double
typedef double db;
using namespace std;

const int MaxN = 200100;
const int Mod = 1e9 + 7;
const int ALPH = 26;
const int TOT = 200+ALPH;
inline int f(char a) {
  return a - 'a';
}

int N;
string S;
vector<pii> best(ALPH+1);

int longestWithKDistinct(int K) {
  int ret = -1;
  int L = 0, R = 0; // [L, R>
  int num_distinct = 0;
  vector<int> cnt(TOT);

  while (true) {
    assert(L <= R);
    if (L == R) assert(num_distinct == 0);
    
    if (num_distinct == K && R-L > ret) {
      ret = R-L;
      best[K].X = L;
      best[K].Y = R;
    }
    if (num_distinct <= K) {
      if (R == N) break;
      int c = S[R];
      if (cnt[c] == 0) {
	num_distinct++;
      }
      cnt[c]++;
      R++;
    }
    else {
      int c = S[L];
      if (cnt[c] == 1) {
	num_distinct--;
      }
      cnt[c]--;
      L++;
    }
  }

  //  TRACE(K _ ret _ best[K].X _ best[K].Y);
  return ret;
}

void solve() {
  double ans = 1e9;
  int ind = -1;
  FOR(K, 1, ALPH+1) {
    int num = longestWithKDistinct(K);
    if (num != -1) {
      double new_ans = (double)K / num;
      //      TRACE(K _ new_ans);
      if (new_ans < ans) {
	ans = new_ans;
	ind = K;
      }
    }
  }

  cout << best[ind].X + 1 << " " << best[ind].Y << endl; 
}

void load() {
  cin >> N >> S;
}

int main() {
  ios_base::sync_with_stdio(false);
  load();	
  solve();
  return 0;
}


