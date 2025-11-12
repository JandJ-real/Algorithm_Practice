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
struct node
{
    int left;
    int right;
};
node arr[1000006];

int ans=0;
void dfs(node cur,int deep){
    if(cur.left){
        ans=max(ans,deep+1);
        dfs(arr[cur.left], deep + 1);
    }
    if (cur.right) {
        ans = max(ans, deep + 1);
        dfs(arr[cur.right], deep + 1);
    }
    return;
}
signed main() {
    cin>>n;
for(int i=1;i<n;i++){
    arr[i].left=read();
    arr[i].right = read();
}
//写一个dfs函数
dfs(arr[1],1);
cout<<ans;
}