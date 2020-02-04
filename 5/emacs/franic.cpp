#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

bool bio[MAXN][MAXN];

int n, k, sol = 0;
char c;

int main()
{
	memset(bio, false ,sizeof(bio));
	cin >> n >> k;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			cin >> c;
			if(c == '*')
			{
				bio[i][j] = 1;
				if(i == 0 && j == 0)
					sol++;
				else if((i == 0 && !bio[i][j - 1]) || j == 0 && !bio[i - 1][j])
					sol++;
				else if(i != 0 && j != 0 && !bio[i - 1][j] && !bio[i][j - 1])
					sol++;
			}	
		}
	}
	cout << sol;
	return 0;
}

