#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std; 

const int maxn = 1005;
const int maxq = 200005;
const int inf = 0x3f3f3f3f;

typedef pair<int, int> pii;

int q;
pii qs[maxq];
int sol[maxq];

int root;
vector<int> e[maxn];

int n, m;
int d[maxn];
int subtreeSize[maxn];

bool inTree[maxn];

int dp[maxn][maxn][2][2];

void load() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &d[i]);
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	scanf("%d", &q);
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
	int subSum = 1;
	for (int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == p)
			continue;
		calculateDp(y, x);
		for (int j = 0; j <= subtreeSize[y]; j++)
			for (int l = 0; l < 2; l++)
				for (int r = 0; r < 2; r++)	{
					if (dp[y][j][l][r] == inf)
						continue;
					for (int k = 0; k <= subSum; k++) 
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
	    subSum += subtreeSize[y];
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
		scanf("%d", &qs[i].first);
		qs[i].second = i;
	}
	sort(qs, qs + q);
	int cq = q - 1;
	int i = n;
	while (i >= 0 && cq >= 0) {
		while (cq >= 0 && qs[cq].first >= dp[0][i][0][0]) {
			sol[qs[cq].second] = i;
			cq--;		
		}
		if (cq == -1)
			break;
		while (dp[0][i][0][0] > qs[cq].first)
			i--;
	}
	for (int i = 0; i < q; i++)
		printf("%d\n", sol[i]);
}

int main (void) {
	ios::sync_with_stdio(false);
	load();
	buildTree();
	solve();
	return 0;
}
