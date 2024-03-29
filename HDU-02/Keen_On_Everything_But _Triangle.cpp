/*
*题意：给n根木棍，现在需要选3根组成一个三角形，问这个三角形可能的最大边长
*题解：考虑区间最大的前44个数能否形成三角形，不能则无解。用主席树查询区间第K大，结论可见hdu6512
*/

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mid (l+r)/2
using namespace std;
typedef long long ll;

const int N = 100010;
int n, q, m, cnt = 0;
int a[N], b[N], T[N];
int sum[N << 5], L[N << 5], R[N << 5];
ll tmp[N];
inline int build(int l, int r) {
	int rt = ++cnt;
	sum[rt] = 0;
	if (l < r) {
		L[rt] = build(l, mid);
		R[rt] = build(mid + 1, r);
	}
	return rt;
}

inline int update(int pre, int l, int r, int x) {
	int rt = ++cnt;
	L[rt] = L[pre]; R[rt] = R[pre]; sum[rt] = sum[pre] + 1;
	if (l < r) {
		if (x <= mid) L[rt] = update(L[pre], l, mid, x);
		else R[rt] = update(R[pre], mid + 1, r, x);
	}
	return rt;
}

inline int query(int u, int v, int l, int r, int k) {
	if (l >= r) return l;
	int x = sum[L[v]] - sum[L[u]];
	if (x >= k) return query(L[u], L[v], l, mid, k);
	else return query(R[u], R[v], mid + 1, r, k - x);
}
inline int quersize(int u, int v, int l, int r, int k) {
	if (l >= r) return l;
	int x = sum[L[v]] - sum[L[u]];
	if (x >= k) return query(L[u], L[v], l, mid, k);
	else return query(R[u], R[v], mid + 1, r, k - x);
}
int main() {
	while (~scanf("%d%d", &n, &q)) {
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(b + 1, b + 1 + n);
		m = unique(b + 1, b + 1 + n) - b - 1;

		T[0] = build(1, m);
		for (int i = 1; i <= n; i++) {
			int t = lower_bound(b + 1, b + 1 + m, a[i]) - b;
			T[i] = update(T[i - 1], 1, m, t);
		}
		while (q--) {
			int x, y;
			scanf("%d%d", &x, &y);
			int lim = min(sum[T[y]] - sum[T[x - 1]], 49);
			ll ans = -1;
			int tot = sum[T[y]] - sum[T[x - 1]];
			for (int i = 1; i <= lim; i++) {
				int t = query(T[x - 1], T[y], 1, m, tot);
				tot--;
				tmp[i] = b[t];
			}
			for (int i = 1; i <= lim - 2; i++) {
				if (tmp[i] < tmp[i + 1] + tmp[i + 2]) {
					ans = ll(tmp[i] + tmp[i + 1] + tmp[i + 2]);
					break;
				}
			}
			printf("%lld\n", ans);

		}

	}
	return 0;
}
