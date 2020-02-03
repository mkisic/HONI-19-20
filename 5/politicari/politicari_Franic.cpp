#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair

using namespace std;

const int MAXN = 505;

long long int k;
int n, iduci;
int popis[MAXN][MAXN];
int bio[MAXN][MAXN];
vector<int> slijed;
pair<int,int> stanje;

int main()
{
	memset(bio,false,sizeof(bio));
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> popis[i][j];

	slijed.pb(1);
	slijed.pb(2);
	//y je optuzio x
	stanje = mp(2, 1);
//find list
	int emisija = 2;
	while(1)
	{
		if(bio[stanje.first][stanje.second] != 0)
			break;
		bio[stanje.first][stanje.second] = emisija;
		emisija++;
		
		iduci = popis[stanje.first][stanje.second];
		slijed.pb(iduci);
		stanje = mp(iduci, stanje.first);
	}
//solve
	int len = emisija - bio[stanje.first][stanje.second];
	int poc = bio[stanje.first][stanje.second] - 1;
	//cout << len << " " << poc << endl;
	if(k <= poc)
		cout << slijed[k];
	else 
		cout << slijed[(k - poc) % len + poc - 1];// << " " << (k - poc) % len + poc - 1;
	return 0;
}

