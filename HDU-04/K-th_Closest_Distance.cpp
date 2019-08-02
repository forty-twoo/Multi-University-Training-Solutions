/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-02 18:43
 * @Description: 主席树+二分答案
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6621
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define PI pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 100;
const int Lim = 1e6;
const int MAXN = Lim * 20;
const ll MOD = 998244353;
int ks, m, n;
int a[MAX], rt[MAX];
struct ChairmanTree {
	int lc[MAXN], rc[MAXN], cnt = 0, sum[MAXN];
	inline void init() {
		cnt = 0; mst(lc, 0); mst(rc, 0); mst(sum, 0);
	}
	inline void build(int &o, int l, int r) {
		o = ++cnt;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(lc[o], l, mid); build(rc[o], mid + 1, r);
	}
	inline void insrt(int &o, int pre, int l, int r, int p) {
		o = ++cnt; lc[o] = lc[pre]; rc[o] = rc[pre]; sum[o] = sum[pre] + 1;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (p <= mid) insrt(lc[o], lc[pre], l, mid, p);
		else insrt(rc[o], rc[pre], mid + 1, r, p);
	}
	inline int query(int o, int pre, int l, int r, int L, int R) {
		if (l == r) return sum[o] - sum[pre];
		if (L <= l && r <= R) return sum[o] - sum[pre];
		int mid = (l + r) >> 1;
		int ans = 0;
		if (L <= mid) ans += query(lc[o], lc[pre], l, mid, L, R);
		if (R > mid) ans += query(rc[o], rc[pre], mid + 1, r, L, R);
		return ans;
	}


}T;

int main() {
	scanf("%d", &ks);
	while (ks--) {
		memset(rt, 0, sizeof(rt));
		T.init(); T.build(rt[0], 0, Lim);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			T.insrt(rt[i], rt[i - 1], 0, Lim, a[i]);
		}
		int X = 0, ans;
		int l, r, p, k;
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%d%d", &l, &r, &p, &k);
			l = l ^ X; r = r ^ X; p = p ^ X; k = k ^ X;
			int lb = 0, rb = Lim, mid;
			while (lb < rb) {
				int mid = (lb + rb) >> 1;
				int c = T.query(rt[r], rt[l - 1], 0, Lim, p - mid, p + mid);
				//注意此处二分，我们要选择符合条件的最小的值，因此凡是>=k个数都要缩小区间
				if (c >= k) rb = mid;
				else lb = mid + 1;
			}
			printf("%d\n", lb);
			X = lb;
		}
	}
	return 0;
}
