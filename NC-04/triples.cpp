/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-02 16:41
 * @Description: 模3 位运算
 * @Source: https://ac.nowcoder.com/acm/contest/884/D
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define PI pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 3e3 + 10;
const ll MOD = 998244353;
vector<int> res1, res2;
int T;
ll a;
void solve1() {
	ll ans1, ans2;
	if (res1.size() >= 2) {
		ans1 = a - (1ll << res1[0]);
		ans2 = a - (1ll << res1[1]);
	}
	else if (res1.size() == 1) {
		ans1 = a - (1ll << res1[0]);
		ans2 = (1ll << res1[0]) + (1ll << res2[0]);
	}
	else {
		ans1 = a - (1ll << res2[0]) - (1ll << res2[1]);
		ans2 = (1ll << res2[0]) + (1ll << res2[1]) + (1ll << res2[2]);
	}
	cout << 2 << " " << ans1 << " " << ans2 << endl;
}

void solve2() {
	ll ans1, ans2;
	if (res2.size() >= 2) {
		ans1 = a - (1ll << res2[0]);
		ans2 = a - (1ll << res2[1]);
	}
	else if (res2.size() == 1) {
		ans1 = a - (1ll << res2[0]);
		ans2 = (1ll << res1[0]) + (1ll << res2[0]);
	}
	else {
		ans1 = a - (1ll << res1[0]) - (1ll << res1[1]);
		ans2 = (1ll << res1[0]) + (1ll << res1[1]) + (1ll << res1[2]);
	}
	cout << 2 << " " << ans1 << " " << ans2 << endl;
}


int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		res1.clear(), res2.clear();
		cin >> a;
		for (int i = 0; (a >> i) > 0; i++) {
			ll x = (a >> i);
			if ((a >> i) & 1ll) {
				ll tmp = (1ll << i);
				if (tmp % 3 == 1) res1.push_back(i);
				else if (tmp % 3 == 2) res2.push_back(i);
			}
		}
		if (a % 3 == 0) {
			cout << 1 << " " << a << endl;
		}
		else if (a % 3 == 1) {
			solve1();
		}
		else {
			solve2();
		}
	}
	return 0;
}
