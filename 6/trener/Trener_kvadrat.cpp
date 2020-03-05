#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int MAXN = 75;
const int MAXK = 1505;
const int MOD = 1e9 + 7;

vector<string> prezime[MAXN];

int n, k;
string s;
int memo[MAXN][MAXK];

int add(int a, int b)
{
	long long ret = a + b;
	if(ret < 0)
		ret += MOD;
	if(ret >= MOD)
		ret -= MOD;
	return ret;
}

bool check(string a, string b)
{
	bool left = true, right = true;
	for(int i = 0; i < a.size() - 1; i++)
	{
		if(b[i] != a[i])
			left = false;
		if(b[i] != a[i + 1])
			right = false;
	}
	return (left ||right);
}

int dfs(int x, int y)
{
	if(memo[x][y] != -1)
		return memo[x][y];
	if(x == 0)
		return 1;
	int ret = 0;
	for(int i = 0; i < k; i++)
	{
		if(check(prezime[x][y], prezime[x - 1][i]))
			ret = add(ret, dfs(x - 1, i));
	}
	return memo[x][y] = ret;
}

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	cin >> n >> k;
	memset(memo, -1, sizeof(memo));
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			cin >> s;
			prezime[i].pb(s);
		}
	}
	int sol = 0;
	for(int i = 0; i < k; i++)
	{
		sol = add(sol, dfs(n - 1, i));
	}
	cout << sol;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << endl<< time_spent;
	return 0;
}

