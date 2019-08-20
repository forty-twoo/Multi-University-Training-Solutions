/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-20 13:02
 * @Description: 根据条件建立最小割模型求最大匹配
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6598
 */
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f
#define eps 1e-8
typedef long long ll;
typedef  unsigned long long ull;
using namespace std;
const int MAX = 5e2+10;
const int MAXN=1e5+10;
const int MOD = 998244353;
int n,m;
int S,T;
int head[MAXN],dis[MAX],tot=0;
struct Edge{
	int u,v;
	ll w;
	int nxt;
}edge[MAXN];

void addedge(int u,int v,ll w){
	edge[++tot]={u,v,w,head[u]};
	head[u]=tot;
	edge[++tot]={v,u,w,head[v]};
	head[v]=tot;
}

bool bfs() {
	int s=S;
	queue<int> Q;
	memset(dis, 0, sizeof(dis));
	while (Q.size()) Q.pop();
	Q.push(s); dis[s] = 1;
	while (Q.size()) {
		int x = Q.front(); Q.pop();
		for (int i = head[x]; i; i = edge[i].nxt) {
			int v = edge[i].v; ll w = edge[i].w;
			if (w && !dis[v]) {
				Q.push(v); dis[v] = dis[x] + 1;
				if (v == T) return 1;
			}
		}
	}
	return 0;
}
ll dinic(int x, ll flow) {
	if (x == T) return flow;
	ll rest = flow, k;
	for (int i = head[x]; i&&rest; i = edge[i].nxt) {
		ll w = edge[i].w; int v = edge[i].v;
		if (edge[i].w && dis[v] == dis[x] + 1) {
			k = dinic(v, min(rest, edge[i].w));
			if (!k) dis[v] = 0;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main(){
	//debug;
	//ios::sync_with_stdio(0);
	while(~scanf("%d%d",&n,&m)){
		ll a,b,c;int u,v;ll all=0;
		tot=1;
		for(int i=1;i<=10*m;i++) head[i]=0;
		S=n+1,T=n+2;
		for(int i=1;i<=m;i++){
			scanf("%d%d%lld%lld%lld",&u,&v,&a,&b,&c);
			a*=2,b*=2,c*=2;
			addedge(S,u,(5*a)/8+c/6);
			addedge(S,v,(5*a)/8+c/6);
			addedge(u,T,a/8+(2*c)/3);
			addedge(v,T,a/8+(2*c)/3);
			addedge(u,v,a/4+c/6);
			all+=(a+c+a/4+c/3);
		}
		
		ll maxflow=0,flow = 0;
		while (bfs())
			while (flow = dinic(S, INF)) maxflow += flow;
		ll ans=all-maxflow;
		printf("%lld\n",ans/2);
	}


	return 0;
}

