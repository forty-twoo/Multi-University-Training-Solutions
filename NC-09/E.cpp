/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-15 20:53
 * @Description: 并查集 组合数学
 * @Source: https://ac.nowcoder.com/acm/contest/889/E
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define  INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 5;
int n,m,fa[MAX],sz[MAX],cnt;
ll C[MAX][5],ans=0;
ll ds=0;
void init(){
	C[1][0]=C[1][1]=1;
	for(int i=2;i<=n;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<=4;j++){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
}
int finda(int x){
	return fa[x]==x?x:finda(fa[x]);
}

void solve(int u,int v){
	if(ans==0){
		printf("%lld\n",ans);
		return;
	}

	u=finda(u),v=finda(v);
	if(u==v){
		printf("%lld\n",ans);
		return;
	}
	ll sub=sz[u]*sz[v];
	ds=ds-C[sz[u]][2]-C[sz[v]][2];
	ans=ans-sub*(C[n-sz[u]-sz[v]][2]-ds);
	printf("%lld\n",ans);
	ds+=C[sz[u]+sz[v]][2];
	if(sz[u]<sz[v]) swap(u,v);
	sz[u]+=sz[v];
	fa[v]=u;
}
int main(){
	scanf("%d%d",&n,&m);
	init();
	int u,v;
	ans=C[n][4];
	printf("%lld\n",ans);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		solve(u,v);
	}

	return 0;
}
