/*
 * @Don't panic!
 * @Author: forty-twoo
 * @Date: 2019-08-02 16:08
 * @Description: 后缀自动机+回文树
 * @Source: https://ac.nowcoder.com/acm/contest/884/I
 * @Ps: copy from https://ac.nowcoder.com/acm/contest/view-submission?submissionId=40962138
 */

#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define PI pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 3e3 + 10;
const ll MOD = 998244353;

struct SAM {//下标从1开始，0作为保留位，用于做哨兵
	//如果没有特殊要求，尽量选择合适的自动机，要算好内存
	//经过hdu1000测试，10000个map大概是10kb,对于1e6的字符串，不建议使用后缀自动机
	typedef map<int, int>::iterator IT;
	static const int MAXN = 4e5 + 10;
	int cnt, last, par[MAXN << 1], len[MAXN << 1];
	map<int, int>trans[MAXN << 1];//map用于字符集特别大的时候，注意这里占内存可能会特别大

	int newnode(int parent, int length) {
		par[++cnt] = parent;
		len[cnt] = length;
		trans[cnt].clear();
		return cnt;
	}

	void ini() {
		cnt = 0;
		last = newnode(0, 0);
	}

	void extend(int c) {
		int p = last;
		int np = newnode(1, len[last] + 1);//新建状态，先让parent指向根（1）
		while (p != 0 && trans[p].find(c) == trans[p].end()) {//如果没有边，且不为空，根也是要转移的
			trans[p][c] = np;//他们都没有向np转移的边，直接连过去
			p = par[p];//往parent走
		}
		if (p != 0) {//如果p==0，直接就结束了，什么都不用做，否则节点p是第一个拥有转移c的状态，他的祖先都有转移c
			int q = trans[p][c];//q是p转移后的状态
			if (len[q] == len[p] + 1)par[np] = q;//len[q]是以前的最长串，len[p]+1是合并后的最长串，相等的话，不会影响，直接结束了，
			else {
				int nq = newnode(par[q], len[p] + 1);
				trans[nq] = trans[q];//copy出q来，
				par[np] = par[q] = nq;//改变parent树的形态
				while (trans[p][c] == q) {//一直往上面走
					trans[p][c] = nq;//所有向q连边的状态都连向nq
					p = par[p];
				}
			}
		}
		last = np;//最后的那个节点
	}//SAM到此结束

	long long count_all_substring() {//本质不同的串,不必调用拓扑排序
		long long ret = 0;
		for (int i = 2; i <= cnt; i++) {//不必计算根，因为根太特殊了，它代表的是空串，
			ret += len[i] - len[par[i]];//每个节点存的串都是唯一的right集合，所以对所有状态求和即可
		}
		return ret;
	}

}sam;

struct palindrome_tree {
	static const int maxn = 2e5 + 50;
	int trans[maxn][26], len[maxn], suf[maxn], num[maxn];
	//字典树一样,len代表回文长度,suf指向回文后缀,类似于fail指针，num是最长后缀的数量，经过calc之后是后缀数量
	int last, cnt;//last是上一个回文后缀，cnt是所有节点数

	int new_node(int _len, int _suf, int _num) {//长度，后缀，数量
		for (int i = 0; i < 26; i++)trans[cnt][i] = 0;
		len[cnt] = _len;
		suf[cnt] = _suf;
		num[cnt] = _num;
		return cnt++;
	}

	void ini() {
		cnt = 0;
		int root_even = new_node(0, 1, 0);//=1
		int root_odd = new_node(-1, 1, 0);//=0
		last = root_odd;
	}

	int query_longest_palindrom() {
		int ret = 1;
		for (int i = 0; i < cnt; i++) {
			ret = max(ret, len[i]);
		}
		return ret;
	}


	void extend(char*s, int cur) {
		int w = s[cur] - 'a';//当前结点的值
		int p = last;//上一次匹配到的回文后缀
		while (s[cur - len[p] - 1] != s[cur]) p = suf[p];
		//现在p结点的cur儿子,要么是匹配成功的最长非自身回文后缀,要么是自身这一个字符

		if (!trans[p][w]) {//如果此回文后缀未出现过，要创建节点
			int v = suf[p];//我们来找他的suffix link回边，
			while (s[cur - len[v] - 1] != s[cur])v = suf[v];
			//此时意味着找到了suffix link 是v的儿子
			trans[p][w] = new_node(len[p] + 2, trans[v][w], 0);
		}

		last = trans[p][w];//这一次匹配到的回文后缀
		num[last]++;
	}


	void calc() {
		for (int i = cnt - 1; ~i; i--)num[suf[i]] += num[i];//结点创建顺序保证了suf[i]<i
	}

	int count_all_par() {
		return cnt - 2;
	}

}partree;



const int maxn = 2e5 + 5;
char s[maxn];

int main() {
	while (~scanf("%s", s)) {
		int len = strlen(s);

		sam.ini();
		for (int i = 0; i < len; i++) sam.extend(s[i] - 'a');
		sam.last = 1;
		for (int i = len - 1; i >= 0; i--) sam.extend(s[i] - 'a');

		partree.ini();
		for (int i = 0; i < len; i++) partree.extend(s, i);
		partree.calc();

		//        cout<<partree.count_all_par()<<endl;
		printf("%lld\n", (sam.count_all_substring() + partree.count_all_par()) / 2);
	}
}
