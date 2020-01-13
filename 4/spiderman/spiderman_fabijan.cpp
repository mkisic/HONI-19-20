#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
const int maxh = 1e6 + 5;
int N, K;
int h[maxn];
int sol[maxh];
map <int, int> m;
map <int, int> :: iterator it;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
    	cin >> h[i];
    	m[h[i]]++;
    }

    for (it = m.begin(); it != m.end(); it++)
    {
    	int broj = it -> first;
    	int plus = it -> second;

    	if (broj > K)
    		for (int i = 0; i * broj + K < maxh; i++)
    			sol[i * broj + K] += plus; 
    }

    for (int i = 1; i <= N; i++)
    	cout << sol[h[i]] - (K == 0) << ' ';
    cout << '\n';
}
