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
//由 中 和 后 求先序
string mid;
string back; 
void f(string mid,string back){
    if(mid.empty()) return;
    char root=back[back.size()-1];
    int rootpos=mid.find(root);
    string lmid=mid.substr(0,rootpos);
    string rmid=mid.substr(rootpos+1);
    string lback=back.substr(0,rootpos);
    string rback=back.substr(rootpos,rmid.size());
    cout<<root;
    f(lmid,lback);
    f(rmid,rback);
}
signed main() {
cin>>mid>>back;
f(mid,back);
}