/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-20 14:46
 * @Description: 概率期望 数学
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6595
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
const int MAX = 3e3+10;
const int MAXN=1e5+10;
const int MOD = 998244353;
ll C[MAX][MAX];
ll f[MAX];
ll inv[MAX];//inv of 2^i-1;
ll p[MAX]; //2^i

ll qpow(ll a,int cnt){
	if(cnt==0) return 1;
	ll ans=1;
	while(cnt){
		if(cnt&1){
			ans=(ans*a)%MOD;
		}
		a=(a*a)%MOD;
		cnt>>=1;
	}
	return ans;
}

ll get_inv(ll a){
	return qpow(a,MOD-2);
}

void init(){
	for(int i=1;i<MAX;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
		}
	}
	p[0]=1;
	for(int i=1;i<MAX;i++){
		p[i]=(p[i-1]*2ll)%MOD;
	}
	for(int i=1;i<MAX;i++){
		inv[i]=get_inv(p[i]-1);
	}
	f[1]=0;
	
	for(int i=2;i<MAX;i++){
		//j>=2 ÒòÎªÄæÐò¶ÔµÄ²úÉú±ØÐëÒª³¤¶È´óÓÚ2µÄÊý×é 
		for(int j=2;j<i;j++){
			f[i]=(C[i][j]*f[j]%MOD+f[i])%MOD;
		}
		f[i]=(f[i]+C[i][2]*p[i-1]%MOD)%MOD;
		f[i]=(f[i]*inv[i])%MOD;
	}	
}
int main(){
//	debug;
	init();
	int n;
	while(~scanf("%d",&n)){
		ll ans=0;
		for(int i=2;i<=n;i++){
			ans=(ans+f[i])%MOD;
		}
		ans=ans*get_inv(n)%MOD;
		printf("%lld\n",ans);
	}

	return 0;
}

