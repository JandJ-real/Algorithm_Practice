#include <bits/stdc++.h>
/*
1.本解法n^3
2.位集优化弗洛伊德可到n^2/64
3.找一条直径，双指针枚举满足长度限制的路径 n^2
4.变更偏心距计算方式，使得可以用单调队列 可到n
*/
using namespace std;
#define int long long
inline int read() {
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
int n, s;

vector<pair<int, int>> adj[305];
int temp;

int ans = INT_MAX;
int dist[305][305];
signed main() {
    cin >> n >> s;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INT_MAX;
        }
        dist[i][i] = 0;
    }
    int tempa, tempb, tempc;
    for (int i = 1; i < n; i++) {
        tempa = read();
        tempb = read();
        tempc = read();
        adj[tempa].push_back({tempb, tempc});
        adj[tempb].push_back({tempa, tempc});
        dist[tempa][tempb] = tempc;
        dist[tempb][tempa] = tempc;
    }
    // 1.找出一条直径
    // 2.在这条直径上满足长度限制的路径中找到最小偏心距（就是找出每个点的最远距离？）

    //逃避直径这个点，
    //怎么样遍历所有路径呢：弗洛伊德啊

    
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++)
                {
                for (int j = 1; j <= n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
                }
        }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (dist[i][j] <= s) {
                //怎么求偏心距：发现只与端点有关
                int pian = 0;
                for (int k = 1; k <= n; k++) {
                    pian = max(pian, (dist[i][k] + dist[j][k] - dist[i][j]) / 2);
                }
                ans = min(ans, pian);
                //cout<<"HHH"<<' '<<pian<<endl;
            }
        }
    }
    cout << ans;
}