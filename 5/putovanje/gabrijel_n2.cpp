#include <bits/stdc++.h>
using namespace std;

#define REP(i, a, b) for(int i = a; i < b; i++)

const int maxn = 200100;
int n;

struct edge
{
	int a, ind;
	edge(int _a, int _ind)
	{
		a = _a;
		ind = _ind;
	}
};

vector <vector <edge> > graf;
vector <edge> ve;

long long int rj = 0;

pair <int, int> cijene[maxn];

int kolko_puta[maxn];

bool z;

void rek(int cvor, int rod, int trazim)
{
	if(cvor == trazim)
	{
		z = 1;
		return;
	}
	REP(i, 0, (int)graf[cvor].size())
	{
		if(graf[cvor][i].a == rod) continue;
		rek(graf[cvor][i].a, cvor, trazim);
		if(z)
		{
			kolko_puta[graf[cvor][i].ind]++;
			return;
		}
	}
	return;
}

int main()
{
	scanf("%d", &n);
	graf.insert(graf.begin(), n, ve);
	int a, b, c1, c2;
	int br_ind;
	REP(i, 0, n - 1)
	{
		scanf("%d%d%d%d", &a, &b, &c1, &c2);
		a--; b--;
		graf[a].push_back(edge(b, br_ind));
		graf[b].push_back(edge(a, br_ind));
		cijene[br_ind++] = make_pair(c1, c2);
	}
	REP(i, 0, n - 1)
	{
		z = 0;
		rek(i, -1, i + 1);
	}
	REP(i, 0, n - 1)
	{
		rj += min((long long)kolko_puta[i] * cijene[i].first, (long long) cijene[i].second);
	}
	printf("%lld\n", rj);
	return 0;
}
