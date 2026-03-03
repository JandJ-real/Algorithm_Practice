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
    char data;
    node* left;
    node* right;
};
char arr[30][3];
node point[30];
unordered_map<char, int> mp;
void f(node *cur){
    if(cur==0)return;
cout<<cur->data;
f(cur->left);
f(cur->right);
return;
}
signed main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 2; j++) {
            cin >> arr[i][j];
        }
        point[i].data = arr[i][0];
        mp[arr[i][0]] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (arr[i][1] != '*')
            point[i].left = &point[mp[arr[i][1]]];
        else
            point[i].left = 0;
        if (arr[i][2] != '*')
            point[i].right = &point[mp[arr[i][2]]];
        else
            point[i].right = 0;
    }
    f(&point[1]);
return 0;
}