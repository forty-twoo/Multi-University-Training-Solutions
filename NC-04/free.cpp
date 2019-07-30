/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-07-30 15:31
 * @Description: 最短路
 * @Source: https://ac.nowcoder.com/acm/contest/884/J
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define PI pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 100;
int n, m, S, T, K;
int a[MAX][MAX];
int d[MAX];
int vis[MAX];
typedef pair<int, int> PI;
typedef pair<int, PI> PII;
priority_queue<PII> Q;
int path[MAX];
int tot = 0;
int ans = 0;
priority_queue<int> QQ;
int dijs() {
	memset(d, INF, sizeof(d));
	memset(vis, 0, sizeof(vis));
	d[S] = 0;
	for (int i = 1; i < n; i++) {
		int x = 0;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && (x == 0 || d[j] < d[x])) x = j;
		}
		vis[x] = 1;
		for (int y = 1; y <= n; y++) {
			int w = a[x][y];
			if (w == -1) w = 0;
			if (d[y] > w + d[x]) {
				path[y] = x;
				d[y] = d[x] + w;
			}
		}
	}
	return d[T];
}
void run(int x) {
	int pre = path[x];
	if (a[pre][x] != -1) {
		QQ.push(a[pre][x]);
	}
	else {
		tot++;
	}
	if (x != S) run(pre);
}

int main() {
	//freopen("data.txt", "r", stdin);
	//freopen("my.txt","w",stdout);
	int u, v, w;
	scanf("%d%d%d%d%d", &n, &m, &S, &T, &K);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = INF;

	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		a[u][v] = min(a[u][v], w);
		a[v][u] = min(a[v][u], w);
		PI tmp = make_pair(u, v);
		PII tmpp = make_pair(w, tmp);
		Q.push(tmpp);
	}
	int cnt = K;
	//先选前K条最大边free
	while (cnt--) {
		PII cur = Q.top(); Q.pop();
		a[cur.second.first][cur.second.second] = -1;
		a[cur.second.second][cur.second.first] = -1;
	}
	ans = dijs();
	run(T);
	//最短路中若free掉的边数不够K，可继续选最短路中最大的边free
	if (tot < K) {
		int res = K - tot;
		while (res && QQ.size()) {
			ans -= QQ.top(); QQ.pop();
			res--;
		}
		printf("%d\n", ans);
	}
	else {
		printf("%d\n", ans);
	}

	return 0;
}
