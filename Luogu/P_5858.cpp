#include <bits/stdc++.h>

using namespace std;

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
int n;//个数
int w;//最多容纳w物品
int s;//每次最多拿出s物品
vector<int> arr;
//放入第i种原料时锅内的原料总数包括正在放入锅中的原料
/*
dp[i][j] 放前有i个，拿出j个

*/
signed main()
{
    cin >> n >> w >> s;
    arr.resize(n + 1);
    for (int i = 1; i <= n;i++){
        arr[i] = read();
    } 


}