#include <bits/stdc++.h>

using namespace std;

int n, x, y, cnt;
long long ukupno = 0;
int zapremina[1005], sol[1005];

int main()
{
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> y;
		zapremina[i] = y;
		ukupno += x;
	}
	while(ukupno > 0)
	{
		int m = -1, poz = 0;
		for(int i = 0; i < n; i++)
		{
			if(zapremina[i] > m)
			{
				m = zapremina[i];
				poz = i;
			}
		}
		if(ukupno > m)
		{
			sol[poz] = m;
			zapremina[poz] = -1;
			ukupno -= m;
			cnt++;
		}
		else
		{
			cnt++;
			sol[poz] = ukupno;
			break;
		}
	}
	cout << n - cnt << endl;
	for(int i = 0; i < n; i++)
		cout << sol[i] << " ";
	return 0;
}

