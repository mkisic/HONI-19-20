#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

long long n;
int p, f;
long long patrik[MAXN], fabijan[MAXN];

int main()
{
	cin >> n; 
	cin >> p; 
	for(int i = 0; i < p; i++)
		cin >> patrik[i];
	cin >> f; 
	for(int i = 0; i < f; i++)
		cin >> fabijan[i];
		
	int cnt1 = 0, cnt2 = 0;
	for(int i = 0; i < p; i++)
	{
		bool rijesio = false;
		for(int j = 0; j < f; j++)
		{
			if(patrik[i] == fabijan[j])
				rijesio = true;
		}
		if(!rijesio)
			cnt1++;
	}
	for(int i = 0; i < f; i++)
	{
		bool rijesio = false;
		for(int j = 0; j < p; j++)
		{
			if(fabijan[i] == patrik[j])
				rijesio = true;
		}
		if(!rijesio)
			cnt2++;
	}
	cout << cnt1 << endl << cnt2;
	return 0;
}

