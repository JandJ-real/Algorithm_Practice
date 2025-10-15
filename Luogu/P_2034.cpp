#include <bits/stdc++.h>

using namespace std;
/*
q1:MLE 解决：rolling array
q2:wa 解决：long long
q3:tle 解决：无法解决 现在的dp状态无法进行优化(单调队列优化)
*/
#define int long long
inline int read()
{
    int x = 0, f = 1;     // x: 存储结果, f: 符号标志(1正数, -1负数)
    char ch = getchar();  // 读取第一个字符

    while (!isdigit(ch)) {  // 跳过非数字字符
        if (ch == '-')
            f = -1;      // 遇到负号，设置符号为负
        ch = getchar();  // 继续读取下一个字符
    }

    while (isdigit(ch)) {       // 处理数字部分
        x = x * 10 + ch - '0';  // 将字符转换为数字并累加
        ch = getchar();         // 读取下一个字符
    }

    return x * f;  // 返回结果（考虑符号）
}
int n;
int k;//不能有超过k个连续数字被选择 应该<=k
//vector<int> dp[2];
vector<int> prefix;
vector<vector<int>> dp;

signed main()
{
    /*
    1.由于引入了前缀和，故dp遍历应该从0开始，让prefix[0]派上用场(实际上是因为我发现结果刚好差一而第一个数恰为1)
    */
    //重设状态
    cin>>n>>k;
    
    prefix.resize(n + 1);
    prefix[0] = 0;
    dp.resize(n + 1);
    int temp;
    for (int i = 1; i <= n;i++){
        temp = read();
        prefix[i] = prefix[i - 1] + temp;
        dp[i].resize(2);
    }
    dp[0].resize(2);
    // j+1~i : prefix[i]-prefix[j]
    // 窗口长度：k
    dp[0][0] = 0;
    dp[0][1] = 0;
    deque<int> de;
    de.push_back(0);
    /*
    状态 与 状态转移方程
dp[i][0]表示不取i的最大结果
dp[i][0]=max dp[i-1][0],dp[i-1][1]
dp[i][1]表示取i的最大结果
dp[i][1]=max(dp[j][0]+(j+1~i))
        = ==max(dp[j][0]-prefix[j])==+prefix[i]  j[i-k,i-1]
        这里很关键，将最值比较转换为关于j的单元函数，便于使用单调队列优化，实际上应该是想到这个状态转移方程，才想到使用前缀和存储
*/
    for (int i = 1; i <= n;i++){
        //cout << "i:" << i << endl;
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        int compa = dp[i][0] - prefix[i];
        while (!de.empty() && de.back() - de.front() >= k) {
            de.pop_front();
}
int num = de.front();
dp[i][1] = dp[num][0] - prefix[num] + prefix[i];
while(!de.empty()&&dp[de.back()][0]-prefix[de.back()]<compa){
    de.pop_back();
}
de.push_back(i);
//cout << dp[i][0] << ' ' << dp[i][1] << endl;
    }
    cout << max(dp[n][0], dp[n][1]);
    /*    n = read();
        k = read();

        //j:[0,k]
        int num = read();
        int siz;
        int flag;
        // 总和减去最小的和，使满足条件 --->  不行
        
        dp[i][j] 到i个数，已经连续了j个数的最大值
        
    // 尝试用单调队列 虽然不理解为什么更快

    dp[1].resize(2);
    dp[1][0] = 0;
    dp[1][1] = num;
    int cur = num;    //旧数组的最大值
    int preflag = 1;  //指示旧数组
    for (int i = 2; i <= n; i++) {
        flag = i % 2;  //指示新数组
        dp[flag].resize(min(k + 1, i + 1));
        // cout << "i:" << i << endl;
        // cout << "size:" << dp[i].size() - 1 << endl;
        siz = dp[flag].size();
        num = read();
        for (size_t j = 0; j < siz; j++) {
            
            j=0:dp[i][j]=max(dp[i-1][]);
            j=1:dp[i][j]=dp[i-1][0]+arr[i];
            j=2:dp[i][j]=dp[i-1][1]+arr[i];
            
            if (j) {
                dp[flag][j] = dp[preflag][j - 1] + num;
                cur = max(cur, dp[flag][j]);
            } else {
                dp[flag][j] = cur;
            }
        }
        preflag = flag;  //新变旧
        // cur = cur1;   //不需要的原因是只有第一次(j=0)时会用到cur，在那之后可以更新了
    }
    cout << cur;*/


}