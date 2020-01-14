#include <bits/stdc++.h>

using namespace std;

int n, x, y;
long long ukupno = 0, zapremina;

int main()
{
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> y;
		zapremina = y;
		ukupno += x;
	}
	cout << n - ukupno / zapremina - (ukupno % zapremina != 0) << "\n";
	for(int i = 0; i < n; i++)
	{
		if(ukupno >= zapremina)
		{
			cout << zapremina;
			ukupno -= zapremina;
		}
		else
		{
			cout << ukupno;
			ukupno = 0;
		}
		cout << " ";
	}
	return 0;
}

