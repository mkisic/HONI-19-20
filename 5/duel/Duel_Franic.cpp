#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int n, p, f, idx;
bool patrik[MAXN], fabijan[MAXN];

int main()
{
	for(int i = 0; i < MAXN; i++)
		patrik[i] = fabijan[i] = 0;
	cin >> n; 
	cin >> p; 
	for(int i = 0; i < p; i++)
	{
		cin >> idx;
		patrik[idx] = 1;
	}
	cin >> f; 
	for(int i = 0; i < f; i++)
	{
		cin >> idx;
		fabijan[idx] = 1;
	}
	int cnt1 = 0, cnt2 = 0;
	for(int i = 1; i <= n; i++)
	{
		if(patrik[i] && !fabijan[i])
			cnt1++;
		if(fabijan[i] && !patrik[i])
			cnt2++;
	}
	cout << cnt1 << endl << cnt2;
	return 0;
}

