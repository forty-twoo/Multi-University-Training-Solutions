/*
 * @Don't panic: Allons-y!
 * @Author: forty-twoo
 * @LastEditTime: 2019-09-13 23:01:14
 * @Description: 线段树维护矩阵乘法+dp
 * @Source: https://ac.nowcoder.com/acm/contest/882/E
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
const int MAX=5e4+10;
const int MOD=1e9+7;
using namespace std;
int a[MAX][12],n,m,Q;
struct mat{
	ll a[12][12];
};
mat cun[MAX<<2];
void getmat(mat&c,int x){
	mst(c.a,0);
	for(int i=1;i<=m;i++){
		if(a[x][i]) continue;
		for(int j=i;j>0;j--){
			if(a[x][j]) break;
			c.a[j][i]=1;
		}
		for(int j=i+1;j<=m;j++){
			if(a[x][j]) break;
			c.a[j][i]=1;
		}
	}
}
void matmul(mat &cur,const mat&A,const mat&B ){
	mst(cur.a,0);
	for(int i=1;i<=m;i++){
		for(int k=1;k<=m;k++){
			for(int j=1;j<=m;j++){
				cur.a[i][j]=(cur.a[i][j]+A.a[i][k]*B.a[k][j]%MOD)%MOD;
			}
		}
	}
}

struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	void pushup(int rt){
		matmul(cun[rt],cun[lc],cun[rc]);
	}
	void build(int rt,int l,int r){
		if(l==r){
			getmat(cun[rt],l);
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void change(int rt,int l,int r,int x){
		if(l==r){
			getmat(cun[rt],x);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)  change(lson,x);
		else change(rson,x);
		pushup(rt);
	}

}T;

int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%1d",&a[i][j]);
		}
	}
	T.build(1,1,n);
	int op,x,y;
	for(int i=1;i<=Q;i++){
		scanf("%d%d%d",&op,&x,&y);
		if(op==1){
			a[x][y]^=1;
			T.change(1,1,n,x);
		}else{
			printf("%lld\n",cun[1].a[x][y]);
		}
	}

	return 0;
}
