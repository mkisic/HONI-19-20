#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, p1, p2, f1, f2;
	cin >> n;
	cin >> n >> p1 >> p2;
	cin >> n >> f1 >> f2;
	if(p1 == f1 || p1 == f2)
	{
		if(p2 == f1 || p2 == f2)
			cout << 0 << endl << 0;
		else
			cout << 1 << endl << 1;
	}
	else cout << 1 << endl << 1;
	return 0;
}

