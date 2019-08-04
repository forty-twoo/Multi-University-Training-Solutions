/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-04 16:56
 * @Description: multiset 枚举
 * @Source: https://ac.nowcoder.com/acm/contest/886/D
 */

#include<bits/stdc++.h>
#include <algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e3 + 100;
const ll MOD = 998244353;
int n, k;
int a[MAX];
bool check(int x) {
	multiset<int> S;
	for (int i = 1; i <= n; i++)S.insert(a[i]);
	for (int i = 1; i <= k; i++) {
		int res = x;
		while (S.size()) {
			auto it = S.upper_bound(res);
			if (it != S.begin()) { //注意此处是begin()
				it--;
				res -= *it;
				S.erase(it);
			}
			else {
				break;
			}

		}
	}
	if (S.size() == 0) return true;
	else return false;
}

int main() {
	ios::sync_with_stdio(false);
	int ks, cks = 0;
	cin >> ks;
	while (ks--) {
		cin >> n >> k;
		int sum = 0, maxv = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum += a[i];
			maxv = max(a[i], maxv);
		}
		sum /= k;
		int ans = max(sum, maxv);

		//答案下界sum/k,上界不会证
		while (!check(ans)) {
			ans++;
		}
		cout << "Case #" << ++cks << ": " << ans << endl;

	}

	return 0;
}
