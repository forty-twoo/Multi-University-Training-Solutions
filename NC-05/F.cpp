
/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-09 13:15
 * @Description: 最大团转化为补图的最大独立集
 * @Source: https://ac.nowcoder.com/acm/contest/885/F
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 5e3 + 100;
const ll MOD = 998244353;
int n;
int a[MAX];
vector<int> G[MAX];
int ans;

//二分图最大独立集
struct BI_MAX_Inde_Set {
	int col[MAX], match[MAX], vis[MAX], cnt = 0;

	//染色
	void get_color(int x, int c) {
		col[x] = c;
		for (auto y : G[x]) {
			if (!col[y]) get_color(y, 3 - c);
		}
	}
	//匹配
	bool dfs(int x) {
		vis[x] = 1;
		for (auto y : G[x]) {
			if (vis[y]) continue;
			vis[y] = 1;
			if (!match[y] || dfs(match[y])) {
				match[y] = x;
				match[x] = y;
				return true;
			}
		}
		return false;
	}
	//找最大匹配
	void bin_match() {
		for (int i = 1; i <= n; i++) {
			mst(vis, 0);
			if (col[i] == 1 && dfs(i)) cnt++;
		}
	}
	void max_ind_set() {
		cout << n - cnt << endl;
		mst(vis, 0);
		for (int i = 1; i <= n; i++) {
			if (col[i] == 1 && !match[i])
				dfs(i);
		}

		for (int i = 1; i <= n; i++) {
			if (col[i] == 1 && vis[i]) cout << a[i] << " ";
			if (col[i] == 2 && !vis[i]) cout << a[i] << " ";
		}
		cout << endl;

	}

	void solve() {
		for (int i = 1; i <= n; i++)
			if (!col[i]) get_color(i, 1);
		bin_match();
		max_ind_set();
	}
}MIS;

//判断x和y二进制表示中是否只有1位不同
bool check(int x, int y) {
	x ^= y;
	x -= (x & (-x));
	if (!x) return true;
	else return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (check(a[i], a[j])) {
				G[i].push_back(j); G[j].push_back(i);
			}
		}
	}
	MIS.solve();


	return 0;
}
