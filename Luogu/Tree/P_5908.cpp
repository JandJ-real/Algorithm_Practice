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
int d;
int ans=-1;
int flag[100005];
vector<int> arr[100005];
void f(int cur,int len) {
    flag[cur]=1;
    if (len <= d) {
        ans++;
    } else {
        return;
    }
    for (size_t i = 0; i < arr[cur].size(); i++) {
        if (!flag[arr[cur][i]]) {
            f(arr[cur][i],len+1);
        }
    }
}

signed main() {
    cin >> n >> d;
    int tempa, tempb;
    for (int i = 1; i < n; i++) {
        cin >> tempa >> tempb;
        arr[tempa].push_back(tempb);
        arr[tempb].push_back(tempa);
    }
    memset(flag,0,sizeof(flag));
    f(1,0);
    cout<<ans;
}