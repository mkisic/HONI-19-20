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

int ptr[maxn];
int br_ptr = 0;
set <pair <int, int> > intervali[maxn];
set <pair <int, int> >::iterator it, tr, pom;

long long int rj = 0;

void dodaj(int gdje, int sta)
{
	int l, r;
	pair <int, int> tr_par;
	for(tr = intervali[sta].begin(); tr != intervali[sta].end(); tr++)
	{
		tr_par = *tr;
		l = tr_par.first; r = tr_par.second;
		it = intervali[gdje].lower_bound(tr_par);
		pom = it;
		if(pom != intervali[gdje].begin())
		{
			pom--;
			if(pom -> second == tr_par.first - 1)
			{
				l = pom -> first;
				intervali[gdje].erase(pom);
			}
		}
		if(it != intervali[gdje].end())
		{
			if(it -> first == tr_par.second + 1)
			{
				r = it -> second;
				intervali[gdje].erase(it);
			}
		}
		intervali[gdje].insert(make_pair(l, r));
	}
	return;
}

void rek(int cvor, int rod)
{
	int br_puta;
	int max_vel = -1;
	REP(i, 0, (int)graf[cvor].size())
	{
		if(graf[cvor][i].a == rod) continue;
		rek(graf[cvor][i].a, cvor);
		br_puta = 2 * (int)intervali[ptr[graf[cvor][i].a]].size();
		tr = intervali[ptr[graf[cvor][i].a]].begin();
		pom = intervali[ptr[graf[cvor][i].a]].end();
		pom--;
		br_puta -= (tr -> first == 0 ? 1 : 0) + (pom -> second == n - 1 ? 1 : 0);
		rj += min((long long)graf[cvor][i].c2, (long long)graf[cvor][i].c1 * br_puta); // min za long long?
		max_vel = max(max_vel, (int)intervali[ptr[graf[cvor][i].a]].size());
	}
	if(max_vel == -1)
	{
		ptr[cvor] = br_ptr++;
		intervali[ptr[cvor]].insert(make_pair(cvor, cvor));
		return;
	}
	REP(i, 0, (int)graf[cvor].size())
	{
		if(graf[cvor][i].a == rod) continue;
		if((int)intervali[ptr[graf[cvor][i].a]].size() == max_vel)
		{
			ptr[cvor] = ptr[graf[cvor][i].a];
			break;
		}
	}
	REP(i, 0, (int)graf[cvor].size())
	{
		if(graf[cvor][i].a == rod) continue;
		if((int)intervali[ptr[graf[cvor][i].a]].size() == max_vel)
		{
			max_vel = -1;
			continue;
		}
		dodaj(ptr[cvor], ptr[graf[cvor][i].a]);
	}
	int pom_ptr = br_ptr++;
	intervali[pom_ptr].insert(make_pair(cvor, cvor));
	dodaj(ptr[cvor], pom_ptr);
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
	rek(0, -1);
	printf("%lld\n", rj);
	return 0;
}
