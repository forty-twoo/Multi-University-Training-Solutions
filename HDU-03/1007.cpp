/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-21 13:36
 * @Description: 主席树 
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
const int MAXN=MAX*20;
const int MOD = 998244353;
int ks,n,rt[MAX];
ll w[MAX],m;
ll dc[MAX],tot=0;
struct ChairmanT{
	int lc[MAXN],rc[MAXN],cnt=0,num[MAXN];ll sum[MAXN];
	void init(){
		cnt=0;
	}
	void build(int &o,int l,int r){
		o=++cnt;
		if(l==r){
			sum[o]=num[o]=lc[o]=rc[o]=0;return;
		}
		int mid=(l+r)>>1;
		build(lc[o],l,mid);build(rc[o],mid+1,r);
	}
	void insert(int &o,int pre,int l,int r,int p){
		o=++cnt;lc[o]=lc[pre],rc[o]=rc[pre],sum[o]=sum[pre]+dc[p];num[o]=num[pre]+1;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(p<=mid) insert(lc[o],lc[pre],l,mid,p);
		else insert(rc[o],rc[pre],mid+1,r,p);
	}
	int query(int o,int pre,int l,int r,ll sm){
		if(l==r) {
			if(sum[o] && num[o]){
				ll v=sum[o]/num[o];
				return min(num[o],(int)(sm/v));  //注意此处可选的最多数量
			} else return 0;
		}
		int mid=(l+r)>>1;
		ll delt=sum[lc[o]]-sum[lc[pre]];
		if(delt<=sm) return num[lc[o]]-num[lc[pre]]+query(rc[o],rc[pre],mid+1,r,sm-delt);
		else return query(lc[o],lc[pre],l,mid,sm);

	}

}T;



int main(){
	debug;
	scanf("%d",&ks);
	while(ks--){
		scanf("%d%lld",&n,&m);
		T.init();
		for(int i=1;i<=n;i++){
			scanf("%d",&w[i]);
			dc[i]=w[i];
		}
		sort(dc+1,dc+1+n);
		tot=unique(dc+1,dc+1+n)-(dc+1);
		T.build(rt[0],1,tot);
		for(int i=1;i<=n;i++){
			int t=lower_bound(dc+1,dc+1+tot,w[i])-dc;
			T.insert(rt[i],rt[i-1],1,tot,t);
		}
		for(int i=1;i<=n;i++){
			ll sm=m-w[i];
			int ans=T.query(rt[i-1],rt[0],1,tot,sm);
			printf("%d",i-1-ans);
			if(i==n) printf("\n");
			else printf(" ");
		}
	}
	return 0;
}

