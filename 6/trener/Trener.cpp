#include <bits/stdc++.h>

using namespace std;

const int SOLMOD = 1e9 + 7;
const int MOD = 1e9 + 13;
const int base = 1337;
const int base2 = 10037;
const int MAXN = 80;
const int MAXK = 1005;

string s;
int n, k;
int memo[MAXN][MAXK];
int powers[150][MAXN];

int mul(long long x, long long y, int mod)
{
	long long ret = x * y;
	return ret % mod;
}
int add(int x, int y, int mod)
{
	int ret = x + y;
	if(ret >= mod)
		ret -= mod;
	if(ret < 0)
		ret += mod;
	return ret;
}

int qp(int num, int pot)
{
	if(pot == 1)
		return num;
	if(pot % 2 == 1)
		return mul(num, qp(num, pot - 1), SOLMOD);
	else 
		return qp(mul(num,num, SOLMOD), pot / 2);
}

//O(len) optimizirano
int hash(string word, int left, int right, int baza, int mod)
{
	long long ret = 0;
	for(int i = left; i < word.size() - right; i++)
		ret = add(ret, powers[word[i]][i + 1 - left] * baza, mod); 
	return ret;
}

struct word{
	string word;
	int len;
	int full, full2;
	int left, left2;
	int right, right2;
	
	// O(len) = O(N)
	void create()
	{
		full = hash(word, 0, 0, base, SOLMOD);
		left = hash(word, 0, 1, base, SOLMOD);
		right = hash(word, 1, 0, base, SOLMOD);
		
		full2 = hash(word, 0, 0, base2, MOD);
		left2 = hash(word, 0, 1, base2, MOD);
		right2 = hash(word, 1, 0, base2, MOD);
	}
};

word popis[MAXN][MAXK];

inline bool same(int x, int y, int i)
{
	if(popis[x][y].full != popis[x + 1][i].left && popis[x][y].full != popis[x + 1][i].right)
		return false;
	if(popis[x][y].full2 != popis[x + 1][i].left2 && popis[x][y].full2 != popis[x + 1][i].right2)
		return false;
	return true;
}	

// O(N * K)
int dfs(int x, int y)
{
	if(x == n - 1)
		return 1;
	if(memo[x][y] != -1)
		return memo[x][y];
	int ret = 0;
	for(int i = 0; i < k; i++)
	{
		if(same(x, y, i))
		{
			ret = add(ret, dfs(x + 1, i), SOLMOD);
		}
	}
	return memo[x][y] = ret;
}

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	//optimizacija za potencije kod hashiranja (26 * MAXN)
	for(int i = 'a'; i <= 'z'; i++)
		for(int j = 1; j < MAXN; j++)
			powers[i][j] = qp(i,j);
			
	cin >> n >> k;
	//O(N * K * len) = (N^2 * K)
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			cin >> s;
			popis[i][j].word = s;
			popis[i][j].len = s.size();
			popis[i][j].create();
			memo[i][j] = -1;
		}
	}
	int sol = 0;
	//O(N * K) -- zbog memoizacije
	for(int i = 0; i < k; i++)
		sol = add(sol, dfs(0 , i), SOLMOD);
	cout << sol;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//cout << endl<< time_spent;
	return 0;
}
//(26 * MAXN) + (N^2* K) + (N * K) --> (N ^2* K)
// bez optimizacije potenciranja složenost je NlogN * K^2
//sa mapama bez hashanja je n^2 klogk
