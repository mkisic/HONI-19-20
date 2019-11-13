#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int,int> pii;

int prva, zadnja;
int cntu, cntiz;
vector<int> u, iz;
int n, t, val;
bool pocetak;

void ispis(bool last, int idx)
{
	if(idx == n - 2)
		return;
	if(last)
		cout << u[idx / 2] << " ";
	else 
		cout << iz[idx / 2] << " ";
	ispis(!last, idx + 1);
}

int main()
{
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> t >> val;
		if(t == 5)
		{
			pocetak = true;
			prva = val;
			cntiz++;
		}
		else if(t == 6)
		{
			pocetak = false;
			prva = val;
			cntu++;
		}
		else if(t == 7)
		{
			zadnja = val;
			cntiz++;
		}
		else if(t == 8)
		{
			zadnja = val;
			cntu++;
		}
		else if(t == 1)
		{
			cntiz += 2;
			iz.pb(val);
		}
		else if(t == 4)
		{
			u.pb(val);
			cntu += 2;
		}
	}
	if(cntu != cntiz)
	{
		cout << -1;
		return 0;
	}
	sort(u.begin(),u.end());
	sort(iz.begin(),iz.end());
	reverse(u.begin(),u.end());
	reverse(iz.begin(),iz.end());
	cout << prva << " ";
	ispis(pocetak,0);
	cout << zadnja;
	return 0;
}

