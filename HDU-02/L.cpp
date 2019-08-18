/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-18 15:35
 * @Description: 线段树区间操作
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6602
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f3f3f
#define eps 1e-8
typedef long long ll;
typedef  unsigned long long ull;
using namespace std;
const int MAX = 2e2+10;
int n,C,k,a[MAX],pos[MAX];
vector<int> V[MAX];

struct SEGT{
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
#define ls rt<<1
#define rs rt<<1|1
	
	int sum[MAX<<2],lazy[MAX<<2];
	void pushup(int rt){
		sum[rt]=max(sum[ls],sum[rs]);
	}
	void pushdown(int rt){
		if(lazy[rt]){
			sum[ls]+=lazy[rt];
			sum[rs]+=lazy[rt];
			lazy[ls]+=lazy[rt];
			lazy[rs]+=lazy[rt];
			lazy[rt]=0;
		}
	}
	void build(int rt,int l,int r){
		if(l==r) {
			lazy[rt]=sum[rt]=0;
			return;
		}
		int m=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void insert(int rt,int l,int r,int L,int R,int v){
		if(L<=l && r<=R){
			sum[rt]+=v;
			lazy[rt]+=v;
			return;
		}
		int m=(l+r)>>1;
		pushdown(rt);
		if(L<=m) insert(lson,L,R,v);
		if(R>m) insert(rson,L,R,v);
		pushup(rt);
	}
	int query(int rt,int l,int r){
		if(l==r) {
			return l;
		}
		int m=(l+r)>>1;
		pushdown(rt);
		if(sum[ls]==C) return query(lson);
		else if(sum[rs]==C) return query(rson);
		else return -1;
	}
}T;

int main(){
	while(~scanf("%d%d%d",&n,&C,&k)){
		for(int i=1;i<=C;i++){
			V[i].clear();
			V[i].push_back(0);
		}
		for(int i=0;i<=n;i++) pos[i]=0;
		T.build(1,1,n);

		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			V[a[i]].push_back(i);
		}
		if(k==1){
			printf("%d\n",n);
			continue;
		}
		for(int i=1;i<=C;i++){
			for(int j=1;j<V[i].size();j++){
				pos[V[i][j]]=j;
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			T.insert(1,1,n,i,i,C-1);
			int prep=V[a[i]][pos[i]-1]+1;
			if(i-1>=prep)
				T.insert(1,1,n,prep,i-1,-1);
			if(pos[i]>=k){
				prep=V[a[i]][pos[i]-k]+1;
				T.insert(1,1,n,prep,V[a[i]][pos[i]-k+1],1);
			}
			int q=T.query(1,1,n);
			if(q!=-1){
				ans=max(ans,i-q+1);
			}
		}
		printf("%d\n",ans);
	}

	return 0;
}
