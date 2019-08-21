/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-21 18:53
 * @Description:  二分答案 线段树优化dp
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6606
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
const int MOD = 998244353;
int ks,n,k;
ll w[MAX],sum[MAX];
ll dc[MAX],tot=0;
int dp[MAX];
struct SegT{
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
#define lc rt<<1
#define rc rt<<1|1
	int maxv[MAX<<2];
	void pushup(int rt){
		maxv[rt]=max(maxv[lc],maxv[rc]);
	}

	void build(int rt,int l,int r){
		if(l==r){
			maxv[rt]=-1;
			return;
		}
		int m=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void insert(int rt,int l,int r,int p,int v){
		if(l==r){
			maxv[rt]=v;return;
		}
		int m=(l+r)>>1;
		if(p<=m) insert(lson,p,v);
		else insert(rson,p,v);
		pushup(rt);
	}
	int query(int rt,int l,int r,int L,int R){
		int ans=-1;
		if(L>R) return -1;
		if(L<=l && r<=R){
			return maxv[rt];
		}
		int m=(l+r)>>1;
		if(L<=m) ans=max(ans,query(lson,L,R));
		if(R>m) ans=max(ans,query(rson,L,R));
		return ans;
	}

}T;

bool check(ll x){
	T.build(1,1,tot);
	//注意要先把0位置插进去
	int zerop=lower_bound(dc+1,dc+1+tot,0)-dc;
	T.insert(1,1,tot,zerop,0);

	for(int i=1;i<=n;i++){
		int L=lower_bound(dc+1,dc+1+tot,sum[i]-x)-dc;
		int Ip=lower_bound(dc+1,dc+1+tot,sum[i])-dc;
		int R=tot;
		int p=T.query(1,1,tot,L,R);
		if(p==-1) dp[i]=-1;
		else dp[i]=p+1;
		if(dp[i]>=k) return true;
		T.insert(1,1,tot,Ip,dp[i]);
	}
	return false;
}

int main(){
	//debug;
	scanf("%d",&ks);
	while(ks--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&w[i]);
			sum[i]=sum[i-1]+w[i];
			dc[i]=sum[i];
		}
		dc[n+1]=0;
		sort(dc+1,dc+1+n+1);
		tot=unique(dc+1,dc+1+n+1)-(dc+1);
		ll l=-2e14-10ll,r=2e14+10ll;
		while(l<r){
			ll mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		printf("%lld\n",l);
	}
	return 0;
}
