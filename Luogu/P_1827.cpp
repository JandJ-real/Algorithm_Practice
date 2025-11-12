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
//根据中序 和 前序 序列 给出后序遍历序列
string pre;
string mid;
//递归的途中按后序遍历顺序输出后序遍历字符串
void f(string pre, string mid) {
    if (pre.empty())
        return;
    // string 的find函数是返回下标的
    int root = mid.find(pre[0]);
    string lmid = mid.substr(0, root);
    string rmid = mid.substr(root + 1);
    string lpre = pre.substr(1, root);
    string rpre = pre.substr(root + 1);
    f(lpre, lmid);
    f(rpre, rmid);
    cout << mid[root];
}
signed main() {
    cin >> mid >> pre;
    // cout << pre << mid << endl;
    //递归表达
    f(pre, mid);
}