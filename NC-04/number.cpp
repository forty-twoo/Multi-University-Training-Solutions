/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-07-30 14:17
 * @Description: dp
 * @Source: https://ac.nowcoder.com/acm/contest/884/K
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define PI pair<int,int>
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 100;
char str[MAX];
ll w[MAX], cnt[MAX];

int main() {
	//debug;
	scanf("%s", str + 1);
	int len = strlen(str + 1);
	//w在记录%3的前缀和
	for (int i = 1; i <= len; i++) {
		w[i] = (w[i - 1] + str[i] - '0') % 3;
	}
	ll ans = 0;

	//如果一段区间l~r是300的倍数，则w[r]=w[l-1]
	for (int i = 1; i <= len; i++) {
		if (str[i] == '0') {
			ans++;
			if (str[i - 1] == '0') {
				ans += cnt[w[i]];
			}
		}
		cnt[w[i - 1]]++;
	}
	printf("%lld\n", ans);
	return 0;
}
