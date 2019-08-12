/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-12 22:34
 * @Description: 离散化 线段树维护并查集 支持撤销操作
 * @Source: https://ac.nowcoder.com/acm/contest/888/E
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;

using namespace std;
const int MAX = 2e5 + 10;
const ll MOD = 998244353;
int n, m;
int u[MAX], v[MAX], fa[MAX], sz[MAX];
ll li[MAX], ri[MAX], dc[MAX], tot = 0;
typedef pair<int, int> PI;

struct SEGT {
#define lson 2*rt,l,m
#define rson 2*rt+1,m+1,r

	ll ans = 0;
	vector<PI> G[MAX * 4];
	PI his[MAX * 4];
	int top = 0;
	int finda(int x) {
		return fa[x] == x ? x : finda(fa[x]);
	}

	void merge(int u, int v) {
		int fu = finda(u), fv = finda(v);
		if (fu == fv) {
			his[++top] = make_pair(-1, -1);
			return;
		}
		if (sz[fu] < sz[fv]) swap(fu, fv);
		sz[fu] += sz[fv];
		fa[fv] = fu;
		his[++top] = make_pair(fu, fv);
	}

	void cancel() {
		int x = his[top].first;
		int y = his[top].second;
		top--;
		if (x == -1) return;
		fa[y] = y;
		sz[x] -= sz[y];
	}

	void insert(int rt, int l, int r, int L, int R, int id) {
		if (L <= l && r <= R) {
			PI tmp = make_pair(u[id], v[id]);
			G[rt].push_back(tmp);
			return;
		}
		int m = (l + r) / 2;
		if (L <= m) insert(lson, L, R, id);
		if (R > m) insert(rson, L, R, id);
	}
	void query(int rt, int l, int r) {
		for (auto t : G[rt]) {
			int x = t.first, y = t.second;
			merge(x, y);
		}
		if (l == r) {
			int x = finda(1), y = finda(n);
			if (x == y)
				ans += dc[r + 1] - dc[l];
			for (int i = 0; i < G[rt].size(); i++) cancel();
			return;
		}
		int m = (l + r) / 2;
		query(lson);
		query(rson);
		for (int i = 0; i < G[rt].size(); i++) cancel();

	}
}segt;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%lld%lld", &u[i], &v[i], &li[i], &ri[i]);
		dc[++tot] = li[i]; dc[++tot] = ri[i] + 1ll;
	}
	sort(dc + 1, dc + 1 + tot);
	tot = unique(dc + 1, dc + 1 + tot) - (dc + 1);

	for (int i = 1; i <= m; i++) {
		int x = lower_bound(dc + 1, dc + 1 + tot, li[i]) - dc;
		int y = lower_bound(dc + 1, dc + 1 + tot, ri[i] + 1ll) - dc;
		segt.insert(1, 1, tot, x, y - 1, i);
	}
	segt.query(1, 1, tot);
	printf("%lld\n", segt.ans);

	return 0;
}
