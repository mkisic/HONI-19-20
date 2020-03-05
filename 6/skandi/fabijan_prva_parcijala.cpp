#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int N, M;
int sol = 1e9;
int mask;
int ones;
int max_mask;
string s[maxn];
string c[maxn];

void input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> s[i];
}

void fill_right(int x, int y)
{
	y++;
	while (y < M and s[x][y] == '0') {
		c[x][y] = '1';
		y++;
	}
	return;
}

void fill_down(int x, int y)
{
	x++;
	while (x < N and s[x][y] == '0') {
		c[x][y] = '1';
		x++;
	}
	return;
}

void solve()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (s[i][j] == '1')
				ones++;

	max_mask = (1 << (2 * ones));
	for (int i = 0; i < max_mask; i++)
	{
		int counted = 0;
		for (int j = 0; j < N; j++)
			c[j] = s[j];
		
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				if (s[j][k] == '1')
				{
					if (((1 << counted) & i) == (1 << counted))
						fill_right(j, k);
					counted++;
					if (((1 << counted) & i) == (1 << counted))
						fill_down(j, k);
					counted++;
				}
			}
		}

		bool da = 1;
		for (int j = 0; j < N; j++)
			for (int k = 0; k < M; k++)
				if (c[j][k] == '0') da = 0;

		if (da) 
			if (__builtin_popcount(i) < sol) 
				{sol = __builtin_popcount(i); mask = i;}
	}

	cout << sol << endl;
}

void reconstruct()
{
	int counted = 0;

	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			if (s[j][k] == '1')
			{
				if (((1 << counted) & mask) == (1 << counted))
					cout << j + 1 << ' ' << k + 1 << " DESNO\n";
				counted++;
				if (((1 << counted) & mask) == (1 << counted))
					cout << j + 1 << ' ' << k + 1 << " DOLJE\n";
				counted++;
			}
		}
	}
}

int main()
{
	input();
	solve();
	//reconstruct();
}