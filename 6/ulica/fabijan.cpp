#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int N, a;
int postoji[maxn];
int parni;

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> a;
		postoji[a]++;
		if (!(a % 2)) parni++;
	}

	if (2 * parni > N)
		for (int i = 2;;i += 2)
			if (!postoji[i]) {cout << i << '\n'; return 0;}
	if (2 * parni < N)
		for (int i = 1;;i += 2)
			if (!postoji[i]) {cout << i << '\n'; return 0;}
	
}