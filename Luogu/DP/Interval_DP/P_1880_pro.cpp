/*这篇题目已经有四边形不等式的题解了，我就做一点补充吧。

1.为什么长度为n的环可以看做长度为2n的链？
因为n堆石子会合并n-1次，就像并查集一样，最后总会刚好有两端是没有连接的，所以计算最大值可以这样算，然后从中选取长度为n且分数最大的一段链。

2.为什么最大值从可以两个端点的最大者取得？
首先可以把最后一步看成两堆石子合并，倒数第二部看成三堆石子中的两堆合并，再与第三堆合并。
那三堆中哪两堆合并呢？
(用w[i]表示第i堆重量)
前两堆:w1=2w[1]+2w[2]+w[3]
后两堆:w2=w[1]+2w[2]+2w[3]
w2=w[1]+2w[2]+2w[3]（自行推导)
所以应该将1号和3号中较大的一堆与第2堆合并，也就是把一堆合并得尽可能大，所以就有dp2[i][j]=max(dp2[i+1][j],dp2[i][j-1])+cnt[j]-cnt[i-1];
*/

//2倍数组+四边形不等式优化+前缀和优化
#include <cstdio>
#include <iostream>
//会发现。复制数组的方法直接将环结构变成了链式结构，只不过在长度为2n的结构上，遍历上限变成了n
using namespace std;
int cnt[210], s[210][210], dp[210][210], n, temp, te, dp2[210][210], maxn, minn;
//cnt为前缀和
//s用于四边形不等式的优化(只在可能区间进行枚举)
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++){
    scanf("%d", &cnt[i]);
    cnt[i] += cnt[i - 1], s[i][i] = i, s[i + n][i + n] = i + n;
  }

  for (int i = 1; i <= n; i++)
    cnt[i + n] = cnt[i] + cnt[n];
  for (int i = n * 2; i >= 1; i--)
    for (int j = i + 1; j <= n * 2; j++) //参考第1点
    {
      temp = 0x7fffffff;
      dp2[i][j] =
          max(dp2[i + 1][j], dp2[i][j - 1]) + cnt[j] - cnt[i - 1]; //参考第2点
      for (int k = s[i][j - 1]; k <= s[i + 1][j]; k++) {
        if (temp > dp[i][k] + dp[k + 1][j] + cnt[j] - cnt[i - 1]) {
          temp = dp[i][k] + dp[k + 1][j] + cnt[j] - cnt[i - 1];
          te = k;
        }
      }
      dp[i][j] = temp;
      s[i][j] = te;
    }
  minn = 0x7fffffff;
  for (int i = 1; i <= n; i++) {
    minn = min(minn, dp[i][i + n - 1]);
    maxn = max(maxn, dp2[i][i + n - 1]);
  }
  printf("%d\n%d", minn, maxn);
  return 0;
}
