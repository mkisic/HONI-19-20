#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair

int prva, zadnja;
int cnt;
vector<int> u, iz;
int n, t, val;
bool pocetak;

void ispis(bool last, int idx)
{
	if(last)
		cout << u[idx / 2] << " ";
	else 
		cout << iz[idx / 2] << " ";
}

int main()
{
	cin >> n;
	u.clear();
	iz.clear();
	for(int i = 0; i < n; i++)
	{
		cin >> t >> val;
		if(t == 5)
		{
			pocetak = true;
			prva = val;
			cnt++;
		}
		else if(t == 6)
		{
			pocetak = false;
			prva = val;
			cnt--;
		}
		else if(t == 7)
		{
			zadnja = val;
			cnt++;
		}
		else if(t == 8)
		{
			zadnja = val;
			cnt--;
		}
		else if(t == 1)
		{
			cnt += 2;
			iz.pb(val);
		}
		else if(t == 4)
		{
			u.pb(val);
			cnt -= 2;
		}
	}
	if(cnt != 0)
	{
		cout << -1;
		return 0;
	}
	sort(u.begin(), u.end());
	sort(iz.begin(), iz.end());
	cout << prva << " ";
	for(int i = 0; i < n - 2; i++)
	{
		ispis(pocetak, i);
		pocetak = !pocetak;
	}
	cout << zadnja;
	return 0;
}

