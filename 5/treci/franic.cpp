#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;

bool bio[MAXN][MAXN];

int n, k, sol = 0;
char c;

int main()
{
	memset(bio, false ,sizeof(bio));
	cin >> n >> k;
	for(int i = 0; i < n; i++)
	{
		for(int k = 0; k < n; k++)
		{
			cin >> c;
			if(c == '*')
			{
				bio[i][k] = 1;
				if(i == 0 && k == 0)
					sol++;
				else if((i == 0 && !bio[i][k - 1]) || k == 0 && !bio[i - 1][k])
					sol++;
				else if(i != 0 && k != 0 && !bio[i - 1][k] && !bio[i][k - 1])
					sol++;
			}	
		}
	}
	cout << sol;
	return 0;
}

