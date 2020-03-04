#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, M;
	const int maxn = 450;
	string s[500];

	srand(time(0));
	N = rand() % maxn + 5;
	M = 10;
	for (int i = 0; i < N; i++) 
	{
		s[i] = "";
		for (int j = 0; j < M; j++)
		{
			if (!i) s[i] += '1';
			else if (!j) s[i] += '1';
			else
			{
				int x = rand() % 4;
				if (!x) s[i] += '1';
				else s[i] += '0';
			}
		}
	}

	cout << N << ' ' << M << endl;
	for (int i = 0; i < N; i++)
		cout << s[i] << endl;

}