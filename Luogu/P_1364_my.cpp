#include <bits/stdc++.h>

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
int n;
struct node {
    int data;
    int left;
    int right;
};
node arr[105];
int dist[105][105];

//想法：记录任意两个顶点之间的距离  弗洛伊德
int ans = 10000000;
signed main() {
    cin >> n;
    for (int i = 0; i <= 104; i++) {
        for (int j = 0; j <= 104; j++) {
            dist[i][j] = 1000;
        }
    }
    for (int i = 1; i <= n; i++) {
        arr[i].data = read();
        arr[i].left = read();
        arr[i].right = read();

        dist[i][i] = 0;
        dist[i][arr[i].left] = 1;
        dist[arr[i].left][i] = 1;
        dist[i][arr[i].right] = 1;
        dist[arr[i].right][i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }
    /*for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            cout<<i<<' '<<j<<' '<<dist[i][j]<<endl;
        }
    }*/

    for (int i = 1; i <= n; i++) {
        int temp = 0;
        for (int j = 1; j <= n; j++) {
            temp += dist[i][j] * arr[j].data;
        }
        ans = min(ans, temp);
    }
    cout << ans;
}