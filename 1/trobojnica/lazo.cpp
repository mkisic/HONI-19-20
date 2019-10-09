#include <bits/stdc++.h>
#include <unistd.h>

#define FOR(a, b, c) for(int a = (b), _for = (c); a < _for; ++a)
#define REP(a, b) FOR(a, 0, b)
#define ll long long
#define pii pair < int, int >
#define x first
#define y second
#define pb push_back

using namespace std;

const int MAX = 100000;
const int Q = 100000;
const int M = 1e7;

int c, d, base, t;
int cnt[MAX + 5];
int x, cntx;
vector < int > sol;

int sum_base(ll a){
	int ret = 0;
	while (a){
		ret += a % base;
		a /= base;
	}
	return ret;
}

void END(){
	REP (i, t) printf ("%d\n", sol[i]);
	exit(0);
}

void f(int len, ll val, int sum){
	if (len * (base - 1) + sum < x) return;
	if (len == 0){
		if (val % c == d){
			sol.push_back(val / c);
			if ((int)sol.size() == t) END();
		}
		return;
	}
	if (len == 1){
		f(0, val * base + (x - sum), x);
		return;
	}
	FOR(i, 0, min(base, x - sum)) f(len - 1, val * base + i, sum + i);
}

int main(){
	srand(time(0)*getpid());
//	scanf ("%d %d %d %d\n",&c,&d,&base,&t);
	int MVAL = 1000;
	c = rand() % MVAL + 1, d = rand() % c, base = rand() % (MVAL - 5) + 5; t = 200000;
	cerr << c << " " << d << " " << base << " " << t << endl;
	ll a;
	FOR(i, 0, Q){
		do{
			a = (ll)(rand() % M) * c + d;
		} while(a < 0);
		int val = sum_base(a);
		if (val < MAX && val >= 0) cnt[val]++;
	}
	REP(i, MAX) if (cntx < cnt[i]){ cntx = cnt[i], x = i; }
	for (int i = 0; ;++i)
		FOR(j, 1, base)
			f(i, j, j);
	return 0;
}
