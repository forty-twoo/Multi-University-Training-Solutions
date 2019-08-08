/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-09 01:40
 * @Description: 枚举左右区间 线段树维护最大字段和
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6638
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
#define lson 2*rt,l,m
#define rson 2*rt+1,m+1,r
typedef long long ll;
using namespace std;
const int MAX = 2e3 + 10;
const ll MOD = 998244353;
int n;
int xb[MAX], xt = 0, xm;
int yb[MAX], yt = 0, ym;
struct Node {
	int x, y;
	ll w;
	bool operator<(const Node&X) {
		if (x == X.x) return y < X.y;
		return x < X.x;
	}
}node[MAX];
ll msum[MAX * 4], presum[MAX * 4], lstsum[MAX * 4], allsum[MAX * 4];

void build(int rt, int l, int r) {
	msum[rt] = presum[rt] = lstsum[rt] = allsum[rt] = 0;
	if (l == r) return;
	int m = (l + r) / 2;
	build(lson); build(rson);
}

void push_up(int rt) {
	presum[rt] = max(allsum[rt * 2] + presum[rt * 2 + 1], presum[rt * 2]);
	lstsum[rt] = max(lstsum[rt * 2] + allsum[rt * 2 + 1], lstsum[rt * 2 + 1]);
	allsum[rt] = allsum[rt * 2] + allsum[rt * 2 + 1];
	msum[rt] = max(msum[rt * 2], msum[rt * 2 + 1]);
	msum[rt] = max(msum[rt], lstsum[rt * 2] + presum[rt * 2 + 1]);

}

void insert(int rt, int l, int r, int p, int val) {
	if (l == r) {
		allsum[rt] += val;
		presum[rt] = lstsum[rt] = msum[rt] = max(allsum[rt], 0ll);
		return;
	}
	int m = (l + r) / 2;
	if (p <= m)insert(lson, p, val);
	else insert(rson, p, val);
	push_up(rt);
}

int main() {
	//freopen("1005.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		ll ans = 0;
		scanf("%d", &n);
		xt = 0, yt = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d", &node[i].x, &node[i].y, &node[i].w);
			xb[++xt] = node[i].x;
			yb[++yt] = node[i].y;
		}
		sort(xb + 1, xb + 1 + xt);
		sort(yb + 1, yb + 1 + yt);
		xm = unique(xb + 1, xb + 1 + xt) - (xb + 1);
		ym = unique(yb + 1, yb + 1 + yt) - (yb + 1);
		sort(node + 1, node + 1 + n);
		int lb, rb;
		build(1, 1, ym);
		for (int i = 1; i <= n; i++) {
			lb = lower_bound(xb + 1, xb + 1 + xm, node[i].x) - xb;
			int j = i;
			for (; j <= n; j++) {
				int t = lower_bound(xb + 1, xb + 1 + xm, node[j].x) - xb;
				int yy = lower_bound(yb + 1, yb + 1 + ym, node[j].y) - yb;
				if (t != lb) break;
				insert(1, 1, ym, yy, node[j].w);
			}
			i = j;
			rb = lower_bound(xb + 1, xb + 1 + xm, node[j].x) - xb;
			for (; j <= n; j++) {
				int t = lower_bound(xb + 1, xb + 1 + xm, node[j].x) - xb;
				int yy = lower_bound(yb + 1, yb + 1 + ym, node[j].y) - yb;
				if (t != rb) {
					//query:
					ans = max(ans, msum[1]);
					rb = t;
				}
				insert(1, 1, ym, yy, node[j].w);
			}
			ans = max(ans, msum[1]);
			build(1, 1, ym);
		}
		cout << ans << endl;

	}


	return 0;
}
