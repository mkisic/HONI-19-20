#include <bits/stdc++.h>
using namespace std;

#define REP(i, a, b) for(int i = a; i < b; i++)

const int maxn = 200100;
int n;

struct edge
{
	int a, c1, c2;
	edge(int _a, int _c1, int _c2)
	{
		a = _a;
		c1 = _c1;
		c2 = _c2;
	}
};

vector <vector <edge> > graf;
vector <edge> ve;

long long int rj = 0;

int br = 0;
int ind[maxn];

int fen[maxn];

void ubaci(int x, int sta)
{
	for(int i = x; i < maxn; i += i&-i)
	{
		fen[i] += sta;
	}
	return;
}

int daj(int x)
{
	int ret = 0;
	for(int i = x; i > 0; i -= i&-i)
	{
		ret += fen[i];
	}
	return ret;
}

void rek(int cvor, int rod)
{
	ind[cvor] = br++;
	REP(i, 0, (int)graf[cvor].size())
	{
		if(graf[cvor][i].a != rod) rek(graf[cvor][i].a, cvor);
	}
	return;
}

void rek2(int cvor, int rod, int poz)
{
	REP(i, 0, (int)graf[cvor].size())
	{
		if(graf[cvor][i].a != rod)
		{
			rj += min((long long)daj(poz) * graf[cvor][i].c1, (long long)graf[cvor][i].c2);
			rek2(graf[cvor][i].a, cvor, poz + 1);
		}
	}
	return;
}

int main()
{
	scanf("%d", &n);
	graf.insert(graf.begin(), n, ve);
	int a, b, c1, c2;
	REP(i, 0, n - 1)
	{
		scanf("%d%d%d%d", &a, &b, &c1, &c2);
		a--; b--;
		graf[a].push_back(edge(b, c1, c2));
		graf[b].push_back(edge(a, c1, c2));
	}
	int poc;
	REP(i, 0, n)
	{
		if((int)graf[i].size() == 1)
		{
			poc = i;
			break;
		}
	}
	rek(poc, -1);
	REP(i, 0, n - 1)
	{
		a = ind[i]; b = ind[i + 1];
		if(a > b) swap(a, b);
		ubaci(a + 1, 1);
		ubaci(b + 1, -1);
	}
	rek2(poc, -1, 1);
	printf("%lld\n", rj);
	return 0;
}
