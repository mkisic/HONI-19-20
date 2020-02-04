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
		
	int cnt = 0;
	for(int i = 0; i < p; i++)
		for(int j = 0; j < f; j++)
			if(fabijan[j] == patrik[i])
				cnt++;
	cout << p - cnt << endl << f - cnt << endl;
	return 0;
}

