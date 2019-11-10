#include <bits/stdc++.h>

using namespace std;

long long n, x, a, b;

int main()
{
	cin >> n >> x;
	for(int i = 0; i < n; i++)
	{
		cin >> a >> b;
		x += (-a + b);	
	}
	cout << x;
	return 0;
}

