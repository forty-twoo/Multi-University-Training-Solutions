/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-16 23:09
 * @Description: 回文自动机
 * @Source: http://acm.hdu.edu.cn/showproblem.php?pid=6599
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
const int MAX = 3e5+100;
char str[MAX];
ull f[MAX],bs[MAX],invf[MAX];
int Len;
void Hashpre(){
	bs[0]=1;
	for(int i=1;i<MAX;i++){
		bs[i]=bs[i-1]*131;
	}
}
void Hash(int len){
	for(int i=1;i<=len;i++){
		f[i]=f[i-1]*131+(str[i]-'a'+1);
	}
	for(int i=1;i<=len;i++){
		invf[i]=invf[i-1]*131+(str[len-i+1]-'a'+1);
	}
}
int fuck[MAX],ans[MAX];

//回文自动机模板
struct PalidromTree {
#define N 26
	int nxt[MAX][N]; //nxt指针与字典树类似，指向的串为当前串两端加同一个字符构成
	int fail[MAX]; //fail指针，失配后跳转到fail指针指向的节点
	int cnt[MAX]; //节点i代表的本质不同的串的个数(建树时求出的不是完全的，最后count()函数跑一遍后才是正确的
	int num[MAX]; //以节点i代表的最长回文串的最右端点为回文结尾的回文串种类个数
	int len[MAX]; //节点i表示的回文串的长度
	int S[MAX]; //存放添加的字符
	int id[MAX]; //节点i的回文串的最后一个元素的下一个
	int last; //指向上一个字符所在节点，方便下一次add
	int n; //字符数组指针
	int p; //节点指针

	int newnode(int l) { //新建节点
		for(int i = 0; i < N; i++) nxt[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0); //插入偶根
		newnode(-1); //插入奇根
		last = 0;
		n = 0;
		S[n] = -1; //开头放一个字符集中没有的字符，减少特判
		fail[0] = 1; //偶根的fail指向奇根
	}
	int get_fail(int x) {
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}

	void add(int c) {
		c -= 'a';
		S[++n] = c;
		int cur = get_fail(last); //通过上一个回文串找这个回文串的匹配位置
		if(!nxt[cur][c]) {  //如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
			int now = newnode(len[cur] + 2);
			fail[now] = nxt[get_fail(fail[cur])][c]; //建立fail指针，失配后跳转
			nxt[cur][c] = now;
			num[now] = num[fail[now]] + 1;

			//判断该回文串的前半段是否为回文串,使用字符串hash
			int l=n-len[now]+1,r=n;
			int mid=(l+r)/2;
			int plen=mid-l+1;
			if(plen%2==1){
				int ll=l,rr=mid;
				int m=(ll+rr)/2;
				int nl=Len-rr+1,nm=Len-m+1;
				if(f[m-1]-f[ll-1]*bs[m-ll] == invf[nm-1]-invf[nl-1]*bs[m-ll]) fuck[now]=1;
			} else{
				int ll=l,rr=mid;
				int m=(ll+rr)/2;
				int nl=Len-rr+1,nm=Len-(m+1)+1;
				if(f[m]-f[ll-1]*bs[m-ll+1] == invf[nm]-invf[nl-1]*bs[m-ll+1]) fuck[now]=1;
			}

		}
		last = nxt[cur][c];
		cnt[last]++;
		id[last] = n;
	}
	void count() {
		for(int i = p - 1; i >= 0; i--) {
			cnt[fail[i]] += cnt[i]; //fail树上父亲累加儿子的个数
		}
		for(int i = p - 1; i >= 2; i--) {
			ans[len[i]]=ans[len[i]]+(fuck[i])*cnt[i];
		}
	}
}pam;
int main(){
	//debug;
	Hashpre();
	while(scanf("%s",str+1)==1){
		pam.init();
		int len=strlen(str+1);
		for(int i=1;i<=len+10;i++)
			ans[i]=fuck[i]=0;

		Len=len;
		Hash(len);
		for(int i=1;i<=len;i++) pam.add(str[i]);
		pam.count();
		printf("%d",ans[1]);
		for(int i=2;i<=len;i++){
			printf(" %d",ans[i]);
		}

		printf("\n");
	}
	return 0;
}
