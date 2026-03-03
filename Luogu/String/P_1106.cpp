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
string str;
int n;
map<int, int> mp;
int flag[255];
list<int> arr;
//贪心：每次删从左往右的极大值，如果单调则删除最后一个
signed main() {
    cin >> str;
    cin >> n;
    int len = str.size();
    // cout << len << endl;
    for (int i = 0; i < len; i++) {
        arr.push_back(str[i] - '0');
    }
    int flag2;
    // int flag=0;
    while (n--) {
        // cout << "n:" << n << endl;
        //  flag=0;
        flag2 = 0;
        auto it = arr.begin();
        for (int i = 1; i < len; i++) {
            auto it2 = it++;
            if (*it < *(it2)) {
                // cout<<"erase:"<<*it2<<endl;
                arr.erase(it2);
                flag2 = 1;
                break;
            }
        }
        if (!flag2) {
            arr.pop_back();
        }
    }
    while(arr.front() == 0&&arr.size()>1) {
        arr.pop_front();
    }
    for (auto it = arr.begin(); it != arr.end(); it++) {
        cout << *it;
    }
}
