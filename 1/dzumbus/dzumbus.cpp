#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std; 

const int maxn = 505;
const int inf = 0x3f3f3f3f;

int q;

int root;
vector<int> e[maxn];

int n, m;
int d[maxn];
int subtreeSize[maxn];

bool inTree[maxn];

int dp[maxn][maxn][2][2];

void load() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> d[i];
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	cin >> q;
}

void dfs(int x, int p) {
	inTree[x] = 1;
	subtreeSize[x] = 1;
	for (int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];	
		if (y != p) {
			dfs(y, x);
		    subtreeSize[x] += subtreeSize[y];
		}
	}
}

void buildTree() {
	root = 0;
	d[root] = inf;
	for (int i = 1; i <= n; i++) 
		if (inTree[i] == false) {
			e[root].push_back(i);
			dfs(i, -1);		
		}
}

void calculateDp(int x, int p) {	
	vector<int> updatedDp[2][2];	
	for (int i = 0; i < 2; i++)
		for (int k = 0; k < 2; k++)	
			for (int j = 0; j <= n; j++)
				updatedDp[i][k].push_back(inf);	
	dp[x][0][0][0] = 0;
	dp[x][0][1][0] = d[x];
	for (int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == p)
			continue;
		calculateDp(y, x);
		for (int j = 0; j <= min(n, subtreeSize[y]); j++)
			for (int l = 0; l < 2; l++)
				for (int r = 0; r < 2; r++)	{
					if (dp[y][j][l][r] == inf)
						continue;
					for (int k = 0; k <= min(n - j, subtreeSize[x]); k++) 
						for (int o = 0; o < 2; o++)
							for (int s = 0; s < 2; s++) {
								if (dp[x][k][o][s] == inf)
									continue;
								int cnt = j + k;
								int newS = s;
								if (o == 1 && l == 1) {
									cnt += 2 - r - s;
									newS = 1;
								}
								int cost = dp[y][j][l][r] + dp[x][k][o][s];
								if (dp[x][cnt][o][newS] > cost)
									updatedDp[o][newS][cnt] = min(updatedDp[o][newS][cnt], cost);
							}
					}
		for (int j = 0; j <= n; j++)
			for (int k = 0; k < 2; k++)
				for (int l = 0; l < 2; l++)	{
					dp[x][j][k][l] = min(dp[x][j][k][l], updatedDp[k][l][j]);
					updatedDp[k][l][j] = inf;
				}
	}
}

void solve() {
	memset(dp, inf, sizeof dp); 
	calculateDp(root, -1);
	for (int i = 0; i < q; i++) {
		int cs;
		cin >> cs;
		int sol = 0;
		for (int j = 1; j <= n; j++)
			if (dp[0][j][0][0] <= cs)
				sol = max(sol, j);
		cout << sol << endl;
	}
}

int main (void) {
	ios::sync_with_stdio(false);
	load();
	buildTree();
	solve();
	return 0;
}
