#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

bool patrik[MAXN], fabijan[MAXN];
int x, n, p ,f;

int main()
{
	for(int i = 0; i < MAXN; i++)
		patrik[i] = fabijan[i] = 0;
	cin >> n;
	cin >> p;
	for(int i = 0; i < p; i++)
	{
		cin >> x;
		patrik[x] = 1;
	}
	cin >> f;
	for(int i = 0; i < f; i++)
	{
		cin >> x;
		fabijan[x] = 1;
	}
	int sol1 = 0, sol2 = 0;
	for(int i = 1; i <= n; i++)
	{
		if(patrik[i] && !fabijan[i])
			sol1++;
		if(fabijan[i] && !patrik[i])
			sol2++;
	}
	cout << sol1 << endl << sol2;
	return 0;
}

