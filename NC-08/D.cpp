/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-13 16:27
 * @Description: 三维BIT (类似天使玩偶cdq那道题，区别在于此题为三维，且整个立方体体积不超过1e5，因此可以不用cdq分治
 * @Source: https://ac.nowcoder.com/acm/contest/888/D
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define  INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 8e5 + 10;

int n, m, h, q;
int op, x, y, z;

struct BIT {
	int a[MAX];
	int gethash(int x, int y, int z) {
		return x * h * m + y * h + z;
	}
	void init() {
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				for (int k = 0; k <= h; k++) {
					int num = gethash(i, j, k);
					a[num] = 0;
				}
			}
		}
	}

	void insert(int x, int y, int z) {
		for (int i = x; i <= n; i += lowbit(i)) {
			for (int j = y; j <= m; j += lowbit(j)) {
				for (int k = z; k <= h; k += lowbit(k)) {
					int num = gethash(i, j, k);
					a[num] = max(a[num], x + y + z);
				}
			}
		}
	}

	int query(int x, int y, int z) {
		int ans = 0;
		for (int i = x; i > 0; i -= lowbit(i)) {
			for (int j = y; j > 0; j -= lowbit(j)) {
				for (int k = z; k > 0; k -= lowbit(k)) {
					int num = gethash(i, j, k);
					ans = max(ans, a[num]);
				}
			}
		}
		if (ans == 0) return INF;
		return (x + y + z) - ans;
	}


}bit[8];
int main() {
	scanf("%d%d%d%d", &n, &m, &h, &q);
	n++, m++, h++;
	for (int i = 0; i < 8; i++)  bit[i].init();
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d%d", &op, &x, &y, &z);
		if (op == 1) {
			//insert
			bit[0].insert(x, y, z);
			bit[1].insert(x, y, h - z);
			bit[2].insert(x, m - y, z);
			bit[3].insert(n - x, y, z);
			bit[4].insert(x, m - y, h - z);
			bit[5].insert(n - x, m - y, z);
			bit[6].insert(n - x, y, h - z);
			bit[7].insert(n - x, m - y, h - z);
		}
		else {
			//query
			int ans = INF;
			ans = min(ans, bit[0].query(x, y, z));
			ans = min(ans, bit[1].query(x, y, h - z));
			ans = min(ans, bit[2].query(x, m - y, z));
			ans = min(ans, bit[3].query(n - x, y, z));
			ans = min(ans, bit[4].query(x, m - y, h - z));
			ans = min(ans, bit[5].query(n - x, m - y, z));
			ans = min(ans, bit[6].query(n - x, y, h - z));
			ans = min(ans, bit[7].query(n - x, m - y, h - z));
			printf("%d\n", ans);
		}

	}
	return 0;
}
