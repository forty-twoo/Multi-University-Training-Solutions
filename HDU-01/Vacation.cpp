/*
*
题意：n+1辆车在一条直路上行驶，每辆车有3个性质：s(距停车线的距离)，v(行驶最大速度)，l(车身长)问最后一辆车车
     头开过终点线的距离，条件：不能超车，若后面的车追上了前面的车则只能跟在后面并速度降为它前面那辆车的速度，
     前面的车即使行驶出了终点线也不能超车或改变速度，只能一直向前行驶，直到最后一辆车达到终点线为止。
题解：最后的情况一定是一辆车堵着后面所有车一起按它的速度行驶，所以枚举每辆车假设它最慢，答案取最大值即可
*
*/

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<stack>
#include<map>
#include<queue>
#include<functional>
/**************/
using namespace std;
#define INF 0x3f3f3f3f
typedef  long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 100;
/**************/
int n;
double s[MAX], l[MAX], v[MAX];
double sum[MAX];
double ans = 0;
double cal(int x) {
    double len = sum[x] + s[x];
    double tm = len / v[x];
    return tm;
}
int main() {
    while (~scanf("%d", &n)) {
        sum[n + 1] = 0;
        ans = 0;
        for (int i = n + 1; i >= 1; i--) scanf("%lf", &l[i]);
        for (int i = n + 1; i >= 1; i--) scanf("%lf", &s[i]);
        for (int i = n + 1; i >= 1; i--) scanf("%lf", &v[i]);
        for (int i = n; i >= 1; i--) {
            sum[i] = sum[i + 1] + l[i];
        }
        for (int i = 1; i <= n + 1; i++) {
            ans = max(ans, cal(i));
        }
        printf("%.7lf\n", ans);

    }
    return 0;
}
