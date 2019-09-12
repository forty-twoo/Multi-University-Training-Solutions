/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-12 18:46:13
 * @Description: 悬线法求第二大全1矩阵
 * @Source: https://ac.nowcoder.com/acm/contest/882/H
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
const int MAX=1100;
using namespace std;
int n, m;
int gra[MAX][MAX];
int Left[MAX][MAX];
int Right[MAX][MAX];
int Up[MAX][MAX];
char str[MAX][MAX];
priority_queue<int> Q;
priority_queue<int> P;
int ans=0;
int preL,preR,preU;
typedef pair<pair<int,int>,int> PI;
map<PI,int> mp;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
			cin >> str[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			gra[i][j]=str[i][j-1]-'0';
			Left[i][j] = Right[i][j] = j;
			Up[i][j] = 1;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 2; j <= m; j++) {
			if (gra[i][j] && gra[i][j-1]) {
				Left[i][j] = Left[i][j - 1];
				
			}
		}
	}


	for (int i = 1; i <= n; i++) {
		for (int j = m - 1; j >= 1; j--) {
			if (gra[i][j] && gra[i][j+1]) {
				Right[i][j] = Right[i][j + 1];
			}
		}
	}

	int ans2 = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if(!gra[i][j]) continue;
			if (gra[i][j] &&gra[i-1][j]&& i>1) {
				Left[i][j] = max(Left[i][j], Left[i - 1][j]);
				Right[i][j] = min(Right[i][j], Right[i - 1][j]);
				Up[i][j] = Up[i - 1][j] + 1;
			}
			int row = Right[i][j] - Left[i][j] + 1;
			ans2 = row*Up[i][j];

			PI py=make_pair(make_pair(Left[i][j],Right[i][j]),Up[i][j]);
			if(mp[py])
				continue;
			mp[py]=1;
			int tmp=max((row-1)*Up[i][j],(row)*(Up[i][j]-1));
			P.push(tmp);
			
			Q.push(ans2);
		}
	}
    if(Q.size()<=1){
        ans=0;
    }else{
        Q.pop();
        int tmp=P.top();
        ans=max(Q.top(),tmp);
    }
    cout<<ans<<endl;
	return 0;

}
