#include <bits/stdc++.h>
#define vi vector <int>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define X first
#define Y second
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 505;
 
int NIL = maxn * maxn - 1;
int N, M;
int n, m;
int Pair[maxn * maxn], Dist[maxn * maxn];
int space_right[maxn][maxn];
int space_down[maxn][maxn];
string s[maxn];
vi Adj[maxn * maxn], Adj1[maxn * maxn], Adj2[maxn * maxn];
map < pii, int > ima1, ima2;
map < int, pii > m1, m2;
map < pii, bool > nula1, nula2;
bool mark[maxn * maxn];
 
bool BFS(){
	queue < int > Q;
	for(int i = 0; i < n; i++){
		Dist[i] = INF;
		if(Pair[i] == NIL){
			Dist[i] = 0;
			Q.push(i);
		}
	}
	Dist[NIL] = INF;
	for(; !Q.empty(); Q.pop()){
		int u = Q.front();
		if(Dist[u] < Dist[NIL]){
			for(int v : Adj[u]){
				if(Dist[Pair[v]] == INF){
					Dist[Pair[v]] = Dist[u] + 1;
					Q.push(Pair[v]);
				}
			}
		}
	}
	return Dist[NIL] != INF;
}
 
bool DFS(int u){
	if(u != NIL){
		for(int v : Adj[u]){
			if(Dist[Pair[v]] == Dist[u] + 1){
				if(DFS(Pair[v])){
					Pair[v] = u;
					Pair[u] = v;
					return 1;
				}
			}
		}
		Dist[u] = INF;
		return 0;
	}
	return 1;
}
 
int Hopcroft_Karp(){
	for(int i = 0;i <= n + m;i++)
		Pair[i] = NIL;
	int matching = 0;
	for(;BFS();){
		for(int i = 0;i < n;i++){
			if(Pair[i] == NIL)
				matching += DFS(i);
		}
	}
	cout << matching << '\n';
}

void alternate(int x, int put)
{
	if (put){
		if (Pair[x] != NIL and !mark[Pair[x]]){
			mark[Pair[x]] = 1;
			alternate(Pair[x], 0);
		}
	}
	else{
		for (int i = 0; i < Adj[x].size(); i++){
			if (Adj[x][i] != Pair[x] and !mark[Adj[x][i]]){
				mark[Adj[x][i]] = 1;
				alternate(Adj[x][i], 1);
			}
		}
	}
}

void konig()
{
	for (int i = 0; i < n; i++)
		if (Pair[i] == NIL)
			{mark[i] = 1; alternate(i, 0);}
	for (int i = 0; i < n; i++)
		mark[i] = !mark[i];
}

void reconstruct()
{
	for (int i = 0; i < n; i++)
		if (mark[i])
			cout << m1[i].X + 1 << ' ' << m1[i].Y + 1 << " DESNO\n";
	for (int i = 0; i < m; i++)
		if (mark[i + n])
			cout << m2[i].X + 1 << ' ' << m2[i].Y + 1 << " DOLJE\n";
}

void make_graph()
{
	for (int i = 0; i < N; i++){
		int cnt = 0;
		for (int j = 0; j < M; j++){
			if (s[i][j] == '1') {cnt = 0; space_right[i][j] = 0;}
			else {cnt++; space_right[i][j] = cnt;}
		}
	}
	for (int i = 0; i < M; i++){
		int cnt = 0;
		for (int j = 0; j < N; j++){
			if (s[j][i] == '1') {cnt = 0; space_down[j][i] = 0;}
			else {cnt++; space_down[j][i] = cnt;}
		}
	}
	for (int i = 1; i < N; i++){
		for (int j = 1; j < M; j++){
			if (s[i][j] == '0'){
				pii poz1 = mp(i, j - space_right[i][j]);
				if (!ima1[poz1] and !nula1[poz1]){
					ima1[poz1] = n;
					if (!n) nula1[poz1] = 1;
					m1[n] = poz1;
					n++;
				}
				pii poz2 = mp(i - space_down[i][j], j);
				if (!ima2[poz2] and !nula2[poz2]){
					ima2[poz2] = m;
					if (!m) nula2[poz2] = 1;
					m2[m] = poz2;
					m++;
				}
				Adj1[ima1[poz1]].pb(ima2[poz2]);
				Adj2[ima2[poz2]].pb(ima1[poz1]);
			}
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < Adj1[i].size(); j++)
			Adj[i].pb(Adj1[i][j] + n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < Adj2[i].size(); j++)
			Adj[i + n].pb(Adj2[i][j]);
}

void input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> s[i];
}

void solve()
{
	make_graph();
	Hopcroft_Karp();
	konig();
}

int main()
{
	input();
	solve();
	reconstruct();
}