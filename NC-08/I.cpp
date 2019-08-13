/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-13 22:24
 * @Description: dfs序 扫描线的思想求区间面积和
 * @Source: https://ac.nowcoder.com/acm/contest/888/I
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define  INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 4e5 + 100;
int n, m_, q;
int li[MAX], ri[MAX];
vector<int> G[MAX];
int in[MAX], out[MAX], cun[MAX], tot = 0;
ll ans[MAX];
struct Node {
	int op, l, r, qid;
};
vector<Node> V[MAX];
void dfs(int x) {
	in[x] = ++tot;
	cun[tot] = x;
	for (auto y : G[x]) dfs(y);
	out[x] = tot;
}

struct SEGT {
#define lson 2*rt,l,m
#define rson 2*rt+1,m+1,r

	ll sum[MAX * 4]; int lazy[MAX * 4];
	void build(int rt, int l, int r) {
		if (l == r) {
			sum[rt] = lazy[rt] = 0;
			return;
		}
		int m = (l + r) / 2;
		build(lson); build(rson);
	}
	void pushdown(int rt, int l, int r) {
		if (lazy[rt]) {
			int m = (l + r) / 2;
			sum[rt * 2] += (ll)lazy[rt] * (ll)(m - l + 1);
			sum[rt * 2 + 1] += (ll)lazy[rt] * (ll)(r - m);
			lazy[rt * 2] += lazy[rt];
			lazy[rt * 2 + 1] += lazy[rt];
			lazy[rt] = 0;
		}

	}
	void insert(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			sum[rt] += (ll)(r - l + 1);
			lazy[rt] += 1;
			return;
		}
		int m = (l + r) / 2;
		pushdown(rt, l, r);
		if (L <= m) insert(lson, L, R);
		if (R > m) insert(rson, L, R);
		sum[rt] = sum[rt * 2] + sum[rt * 2 + 1];
	}

	ll query(int rt, int l, int r, int L, int R) {
		ll ans = 0;
		if (L <= l && r <= R) {
			return sum[rt];
		}
		int m = (l + r) / 2;
		pushdown(rt, l, r);
		if (L <= m) ans += query(lson, L, R);
		if (R > m) ans += query(rson, L, R);
		return ans;
	}
}segt;

int main() {
	scanf("%d%d", &n, &m_);
	int u, v, l, r;
	li[1] = 1, ri[1] = n;
	for (int i = 1; i <= m_; i++) {
		scanf("%d%d%d%d", &u, &v, &l, &r);
		G[u].push_back(v);
		li[v] = l, ri[v] = r;
	}
	dfs(1);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d", &u, &l, &r);
		Node tmp;
		tmp = { -1,l,r,i };
		V[in[u] - 1].push_back(tmp);
		tmp = { 1,l,r,i };
		V[out[u]].push_back(tmp);
	}
	segt.build(1, 1, n);
	for (int i = 1; i <= tot; i++) {
		segt.insert(1, 1, n, li[cun[i]], ri[cun[i]]);
		for (auto x : V[i]) {
			ans[x.qid] += (ll)x.op*segt.query(1, 1, n, x.l, x.r);
		}
	}
	for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);

	return 0;
}

