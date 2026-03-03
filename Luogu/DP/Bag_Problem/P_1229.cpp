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
//根据前序遍历和后续遍历 输出可能的中序遍历数目
string pre;
string back;
int ans = 1;
void f(string pre, string back) {
    // cout<<"pre:"<<pre<<' '<<"back:"<<back<<endl;
    if (pre.size() == 1) {
        return;
    }
    char rightroot = back[back.size() - 2];
    char leftroot = pre[1];
    if (rightroot == leftroot) {
        ans *= 2;
        // cout<<rightroot<<endl;
        pre.erase(0, 1);
        back.erase(back.size() - 1, 1);
        // cout << pre << ' ' << back << endl;
        f(pre, back);
        return;
        // return;
    }
    int rightpos = pre.find(rightroot);
    int leftpos = back.find(leftroot);

    string lpre = pre.substr(1, rightpos - 1);
    string rpre = pre.substr(rightpos);
    string lback = back.substr(0, lpre.size());
    string rback = back.substr(leftpos + 1, rpre.size());
    f(lpre, lback);
    f(rpre, rback);
}
signed main() {
    cin >> pre >> back;
    f(pre, back);
    cout << ans;
}