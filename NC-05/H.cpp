/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-09 16:50
 * @Description: 构图 拓扑排序
 * @Source: https://ac.nowcoder.com/acm/contest/885/H
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 10;
const ll MOD = 998244353;
int cnt[MAX];
int n, m;
char res[5];
char str[MAX];
int id[27][MAX];
int tot = 0;
int mp[MAX];
int ind[MAX];
vector<int> G[MAX];
vector<int> ans;

void topsort() {
	queue<int> Q;
	for (int i = 1; i <= tot; i++) {
		if (!ind[i])
			Q.push(i);
	}
	while (Q.size()) {
		int cur = Q.front(); Q.pop();
		ans.push_back(cur);
		for (auto x : G[cur]) {
			ind[x]--;
			if (ind[x] == 0)Q.push(x);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	int all = m * (m - 1) / 2;
	int len, c;
	tot = 0;
	for (int i = 1; i <= all; i++) {
		mst(cnt, 0);
		cin >> res >> len;
		if (len)
			cin >> str;
		int pre = -1;
		for (int j = 0; j < len; j++) {
			c = str[j] - 'a';
			cnt[c]++;
			if (!id[c][cnt[c]]) {
				id[c][cnt[c]] = ++tot;
				mp[tot] = c;
			}
			if (pre != -1) {
				G[pre].push_back(id[c][cnt[c]]);
				ind[id[c][cnt[c]]]++;
			}
			pre = id[c][cnt[c]];
		}
	}
	topsort();
	if (ans.size() != n) {
		cout << -1 << endl;
	}
	else {
		for (auto x : ans) {
			char c = mp[x] + 'a';
			cout << c;
		}
		cout << endl;
	}
	return 0;
}
