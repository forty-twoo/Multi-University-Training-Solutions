/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-21 13:36
 * @Description: 权值线段树
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6609
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
typedef  unsigned long long ull;
using namespace std;
const int MAX = 2e5+10;
const int MAXN=MAX;
const int MOD = 998244353;
int ks,n;
ll w[MAX],k;
ll dc[MAX],tot=0;

struct SegT{
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
#define lc rt<<1
#define rc rt<<1|1
	int num[MAX*4];ll sum[MAX*4];
	void pushup(int rt){
		sum[rt]=sum[lc]+sum[rc];
		num[rt]=num[lc]+num[rc];
	}
	void build(int rt,int l,int r){
		if(l==r){
			num[rt]=sum[rt]=0;
			return;
		}
		int m=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void insert(int rt,int l,int r,int p){
		if(l==r){
			sum[rt]+=dc[p];
			num[rt]+=1;
			return;
		}
		int m=(l+r)>>1;
		if(p<=m) insert(lson,p);
		else insert(rson,p);
		pushup(rt);
	}
	int query(int rt,int l,int r,ll sm){
		if(l==r){
			return min(num[rt],(int)(sm/dc[l]));
		}
		int m=(l+r)>>1;
		if(sum[lc]<=sm) return num[lc]+query(rson,sm-sum[lc]);
		else return query(lson,sm);
	}

}T;


int main(){
	//debug;
	scanf("%d",&ks);
	while(ks--){
		scanf("%d%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&w[i]);
			dc[i]=w[i];
		}
		sort(dc+1,dc+1+n);
		tot=unique(dc+1,dc+1+n)-(dc+1);
		T.build(1,1,tot);
		for(int i=1;i<=n;i++){
		}
		for(int i=1;i<=n;i++){
			ll sm=k-w[i];
			int ans=T.query(1,1,tot,sm);
			int t=lower_bound(dc+1,dc+1+tot,w[i])-dc;
			T.insert(1,1,tot,t);
			printf("%d ",i-1-ans);
		}
		printf("\n");
	}
	return 0;
}
