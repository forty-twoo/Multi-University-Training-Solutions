/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-16 02:04
 * @Description: 主席树
 * @Source: https://ac.nowcoder.com/acm/contest/889/H
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define INF 0x3f3f3f3f
#define eps 1e-8
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 5;
const int Lim = 1e5;
int n,q;
double a[MAX],pre[MAX];
int rt[MAX];
struct ChairmanT{
	int lc[MAX*20],rc[MAX*20],cnt=0,sum[MAX*20],mxh[MAX*20];
	double val[MAX*20];
	inline void build(int &o,int l,int r){
		o=++cnt;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(lc[o],l,mid);build(rc[o],mid+1,r);
	}
	inline void insert(int &o,int pre,int l,int r,int p){
		o=++cnt;lc[o]=lc[pre];rc[o]=rc[pre];sum[o]=sum[pre]+1;val[o]=val[pre]+p;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(p<=mid) insert(lc[o],lc[pre],l,mid,p);
		else insert(rc[o],rc[pre],mid+1,r,p);
	}
	//查询高度小于hg的树数量
	inline int query(int o,int pre,int l,int r,double hg){
		int num=0;
		if(l==r){
			return 0;
		}
		int mid=(l+r)>>1;
		if(hg<mid)  return num+query(lc[o],lc[pre],l,mid,hg);
		else {
			num=sum[lc[o]]-sum[lc[pre]];
			return num+query(rc[o],rc[pre],mid+1,r,hg);
		}
	}
	//查询高度小于hg的树高度总和
	inline double query1(int o,int pre,int l,int r,double hg){
		double num=0;
		if(l==r){
			return 0;
		}
		int mid=(l+r)>>1;
		if(hg<mid)  return num+query1(lc[o],lc[pre],l,mid,hg);
		else {
			num=val[lc[o]]-val[lc[pre]];
			return num+query1(rc[o],rc[pre],mid+1,r,hg);
		}
	}
}T;


int main(){
//	debug;
	scanf("%d%d",&n,&q);
	T.build(rt[0],1,Lim);
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i]);
		T.insert(rt[i],rt[i-1],0,Lim,a[i]);
		pre[i]=pre[i-1]+a[i];
	}
	int u,v;double x,y;
	for(int i=1;i<=q;i++){
		scanf("%d%d%lf%lf",&u,&v,&x,&y);
		double l=0,r=1e9;
		double cut=(pre[v]-pre[u-1])*x/y;
		while(r-l>eps){
			double mid=(l+r)/2.0;
			double num=T.query(rt[v],rt[u-1],0,Lim,mid);
			double cxk=T.query1(rt[v],rt[u-1],0,Lim,mid);
			double tmpcut=(pre[v]-pre[u-1])-cxk-(double)(v-u+1-num)*mid;
			if(tmpcut<=cut) r=mid;
			else l=mid;
		}
		printf("%.8lf\n",l);
	}

	return 0;
}
