#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int,int> pii;

int prva, zadnja, srednja, pamti;
int cntu, cntiz;
vector<int> desno, lijevo;
int t, val;

void l()
{
	sort(lijevo.begin(),lijevo.end());
	for(int i = lijevo.size() - 1; i>= 0; i--)
		cout << lijevo[i] << " ";
}

void r()
{
	sort(desno.begin(),desno.end());
	for(int i = desno.size() - 1; i>= 0; i--)
		cout << desno[i] << " ";
}
int main()
{
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> t >> val;
		if(t == 5)
		{
			prva = val;
			cntiz++;
		}
		else if(t == 6)
		{
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
			pamti = 1;
			srednja = val;
			cntiz += 2;
		}
		else if(t == 4)
		{
			pamti = 4;
			srednja = val;
			cntu += 2;
		}
		else if(t == 2)
			lijevo.pb(val);
		else
			desno.pb(val);
	}
	if(cntu != cntiz)
	{
		cout << -1;
		return 0;
	}
	cout << prva << " ";
	if(pamti == 1)
		l();
	else
		r();
	cout << srednja << " ";
	if(pamti == 1)
		r();
	else
		l();
	cout << zadnja;
	return 0;
}

