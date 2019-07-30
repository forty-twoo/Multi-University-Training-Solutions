/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-07-30 13:25
 * @Description: 找树的直径
 * @Source: https://ac.nowcoder.com/acm/contest/884/A
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define PI pair<int,int>
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 100;
int n, k;
vector<int> G[MAX];
int imp[MAX];
int dis[MAX], vis[MAX];
void bfs(int ss) {
	mst(dis, 0); mst(vis, 0);
	queue<PI> Q;
	dis[ss] = 0; vis[ss] = 1;
	PI tmp = make_pair(ss, 0);
	Q.push(tmp);
	while (Q.size()) {
		PI cur = Q.front(); Q.pop();
		int u = cur.first;
		vis[u] = 1;
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (vis[v]) continue;
			dis[v] = cur.second + 1;
			tmp = make_pair(v, cur.second + 1);
			Q.push(tmp);
		}
	}
}

int main() {
	//debug;
	scanf("%d%d", &n, &k);
	int u, v;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= k; i++) {
		scanf("%d", &u);
		imp[i] = u;
	}
	bfs(imp[1]);
	int p = -1, maxx = 0;
	for (int i = 1; i <= k; i++) {
		if (dis[imp[i]] > maxx) {
			maxx = dis[imp[i]]; p = imp[i];
		}
	}
	bfs(p);
	int q = -1; maxx = 0;
	for (int i = 1; i <= k; i++) {
		if (dis[imp[i]] > maxx) {
			maxx = dis[imp[i]]; q = imp[i];
		}
	}
	int ans = ceil((double)maxx / 2);
	printf("%d\n", ans);
	return 0;

}
