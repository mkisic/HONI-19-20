#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
int N;
int gol;
int rezultat[3][maxn];
int nerjeseno;
int max_preokret = -1;
int vodstvo[maxn];

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> gol;
		rezultat[1][i] = rezultat[1][i - 1];
		rezultat[2][i] = rezultat[2][i - 1];
		rezultat[gol][i]++;
		if (rezultat[1][i] == rezultat[2][i]) nerjeseno++;
		else if (rezultat[1][i] > rezultat[2][i]) vodstvo[i] = 1;
		else vodstvo[i] = 2;
	}

	for (int i = 1; i < N; i++)
	{
		for (int j = i + 2; j <= N; j++)
		{
			if (vodstvo[i] == 1) {
				if (vodstvo[j] == 2) {
					if (rezultat[1][j] == rezultat[1][i] and rezultat[2][j] - rezultat[1][j] == 1) max_preokret = max(max_preokret, j - i);
				}
			}
			if (vodstvo[i] == 2) {
				if (vodstvo[j] == 1) {
					if (rezultat[2][j] == rezultat[2][i] and rezultat[1][j] - rezultat[2][j] == 1) max_preokret = max(max_preokret, j - i);
				}
			}
		}
	}

	cout << rezultat[1][N] << ' ' << rezultat[2][N] << '\n';
	cout << nerjeseno + 1 << '\n';
	cout << max_preokret << '\n';
}
