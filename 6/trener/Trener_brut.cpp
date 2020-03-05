#include <bits/stdc++.h>

using namespace std;

const int MAXN = 80;
const int MAXK = 800;
const int MOD = 1e9 + 7;

int n, k;
string niz[MAXN][MAXK];

int sol = 0;

bool check(string x, string y)
{
	bool left = true, right = true;
	for(int i = 0; i < y.size() - 1; i++)
	{
		if(x[i] != y[i])
			left = false;
		if(x[i] != y[i + 1])
			right = false;
	}
	return (left || right);
}

int dfs(int x, int y)
{
	if(x >= n - 1)
		return 1;
	int ret = 0;
	for(int i = 0; i < k; i++)
	{
		if(check(niz[x][y], niz[x + 1][i]))
			ret += dfs(x + 1, i);
	}
	return ret;
}

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	cin >> n >> k;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			cin >> niz[i][j];
		}
	}
	for(int i = 0; i < k; i++)
	{
		sol += dfs(0, i);
	}
	cout << sol;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << endl<< time_spent;
	return 0;
}

