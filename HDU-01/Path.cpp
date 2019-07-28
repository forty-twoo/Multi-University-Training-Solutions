/*
*
题意：一张n个点m条边的有向图，现在问你去掉哪些边可以使得从1到n的最短路变长，求最小代价
题解：求一次最短路，用最短路上的所有边重构图跑最大流求最小割
*
*/

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<stack>
#include<map>
#include<queue>
#include<functional>
/**************/
using namespace std;
#define INF 0x3f3f3f3f
typedef  long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
const int MAX = 2e4 + 100;
/**************/
struct Edge {
	int u, v, nxt;
	ll w;
}edge[MAX];
struct CUN {
	int u, v, w;
}cun[MAX];
typedef pair<ll, int> PI;
vector<PI> G[MAX];

ll dis[MAX];
int vis[MAX], head[MAX * 2], tot, n, m;
void add(int u, int v, ll w) {
	edge[++tot].u = u; edge[tot].v = v; edge[tot].w += w, edge[tot].nxt = head[u]; head[u] = tot;
	edge[++tot].u = v; edge[tot].v = u; edge[tot].w = 0; edge[tot].nxt = head[v]; head[v] = tot;
}
ll dijskra() {
	priority_queue<PI, vector<PI>, greater<PI> > Q;
	memset(dis, INF, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[1] = 0;
	PI ss = make_pair(0, 1);
	Q.push(ss);
	while (Q.size()) {
		PI cur = Q.top(); Q.pop();
		if (vis[cur.second]) continue;
		vis[cur.second] = 1;
		int u = cur.second;
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].second; ll w = G[u][i].first;
			if (dis[v] > w + dis[u]) {
				dis[v] = dis[u] + w;
				Q.push(make_pair(dis[v], v));
			}
		}
	}
	return dis[n];
}
void get_new() {
	for (int i = 1; i <= m; i++) {
		int u = cun[i].u, v = cun[i].v, w = cun[i].w;
		if (dis[u] + w == dis[v]) {
			add(u, v, w);
		}
	}


}

bool bfs() {
	int s = 1;
	queue<int> Q;
	memset(dis, 0, sizeof(dis));
	while (Q.size()) Q.pop();
	Q.push(s); dis[s] = 1;
	while (Q.size()) {
		int x = Q.front(); Q.pop();
		for (int i = head[x]; i; i = edge[i].nxt) {
			int v = edge[i].v; ll w = edge[i].w;
			if (w && !dis[v]) {
				Q.push(v); dis[v] = dis[x] + 1;
				if (v == n) return 1;
			}
		}
	}
	return 0;
}
ll dinic(int x, ll flow) {
	if (x == n) return flow;
	ll rest = flow, k;
	for (int i = head[x]; i&&rest; i = edge[i].nxt) {
		ll w = edge[i].w; int v = edge[i].v;
		if (edge[i].w && dis[v] == dis[x] + 1) {
			k = dinic(v, min(rest, edge[i].w));
			if (!k) dis[v] = 0;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main() {
	//freopen("data.txt", "r", stdin);
	//freopen("my.txt","w",stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(edge, 0, sizeof(edge));
		for (int i = 0; i < MAX; i++) G[i].clear();
		ll maxflow = 0;
		memset(head, 0, sizeof(head)); tot = 1;
		int u, v; ll w;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%lld", &u, &v, &w);
			cun[i].u = u, cun[i].v = v, cun[i].w = w;
			G[u].push_back(make_pair(w, v));
		}
		ll mindis = dijskra();
		get_new();
		ll flow = 0;
		while (bfs())
			while (flow = dinic(1, INF)) maxflow += flow;
		printf("%lld\n", maxflow);
	}

	return 0;
}

