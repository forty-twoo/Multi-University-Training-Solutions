/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-04 15:07
 * @Description: 思维+最短路
 * @Source: https://ac.nowcoder.com/acm/contest/886/H
 */

#include<bits/stdc++.h>
#include <algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 100;
const ll MOD = 998244353;
int n, m, sa, sb;
typedef pair<int, int> PI;
vector<int> G[MAX];
int disa[25][MAX], disb[25][MAX], a[MAX], b[MAX], dis[MAX], vis[MAX];
ll mu, zi;
ll Gcd(ll a, ll b) {
	if (b == 0)
		return a;
	return Gcd(b, a % b);
}
void init() {
	mu = zi = 0;
	for (int i = 0; i < MAX; i++) G[i].clear();
	mst(disa, 0); mst(disb, 0);
}
void get_disa(int id) {
	mst(vis, 0);
	queue<int> Q;
	Q.push(a[id]);
	vis[a[id]] = 1;
	while (Q.size()) {
		int cur = Q.front(); Q.pop();
		vis[cur] = 1;
		for (auto to : G[cur]) {
			if (vis[to]) continue;
			disa[id][to] = disa[id][cur] + 1;
			Q.push(to); vis[to] = 1;
		}
	}
}
void get_disb(int id) {
	mst(vis, 0);
	queue<int> Q;
	Q.push(b[id]);
	vis[b[id]] = 1;
	while (Q.size()) {
		int cur = Q.front(); Q.pop();
		vis[cur] = 1;
		for (auto to : G[cur]) {
			if (vis[to]) continue;
			disb[id][to] = disb[id][cur] + 1;
			Q.push(to); vis[to] = 1;
		}
	}
}
void solve(int x, int y) {
	mst(dis, 0); mst(vis, 0);
	queue<int> Q;

	//C每个点到A，B中点的距离合并成dis[i]方便处理
	for (int i = 1; i <= n; i++) dis[i] = disa[x][i] + disb[y][i];
	for (int i = 1; i <= n; i++) {
		Q.push(i); vis[i] = 1;
	}

	//SPFA求多源最短路
	while (Q.size()) {
		int cur = Q.front(); Q.pop();
		vis[cur] = 0;
		for (auto to : G[cur]) {
			if (dis[to] > dis[cur] + 1) {
				dis[to] = dis[cur] + 1;
				if (!vis[to]) {
					Q.push(to); vis[to] = 1;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) mu += dis[i];
}


int main() {
	ios::sync_with_stdio(false);
	int ks, cks = 0;
	cin >> ks;
	while (ks--) {
		cin >> n >> m;
		init();
		int u, v;
		for (int i = 1; i <= m; i++) {
			cin >> u >> v;
			G[u].push_back(v); G[v].push_back(u);
		}
		cin >> sa;
		for (int i = 1; i <= sa; i++) cin >> a[i];
		cin >> sb;
		for (int i = 1; i <= sb; i++) cin >> b[i];

		//分别解决A，B集合中的每个点到所有点的最短路(BFS)
		for (int i = 1; i <= sa; i++) get_disa(i);
		for (int i = 1; i <= sb; i++) get_disb(i);

		//枚举A和B中的每对点
		for (int i = 1; i <= sa; i++) {
			for (int j = 1; j <= sb; j++) {
				solve(i, j);
			}
		}
		zi = (ll)n*(ll)sa*(ll)sb;
		ll t = Gcd(mu, zi);
		mu /= t, zi /= t;
		if (zi == 1) {
			cout << "Case #" << ++cks << ": " << mu << endl;
		}
		else {
			cout << "Case #" << ++cks << ": " << mu << "/" << zi << endl;

		}

	}

	return 0;
}
