#include <bits/stdc++.h>
using namespace std;
#define int long long

/*
原始代码的主要问题分析：
1. 输入处理问题：多余的getchar()和错误的输入逻辑
2. 性能问题：没有利用题目给出的约束条件（P中元素长度≤10）
3. 数据类型使用：使用int而非bool可能造成轻微性能损失
*/

set<string> p;

// 判断字符串是否在集合P中
bool judge(const string& a) {
    return p.find(a) != p.end();
}

signed main() {
    ios::sync_with_stdio(false); // 加速输入输出
    cin.tie(nullptr);
    
    string temp;
    
    // 修复1: 简化集合P的读取逻辑
    while (cin >> temp && temp != ".") {
        p.insert(temp);
    }
    
    // 修复2: 完全重写序列S的输入处理
    // 原问题：使用getline + getchar()组合导致输入错误
    // 解决方案：使用标准的输入流处理
    string s;
    string line;
    
    cin.ignore(); // 清除"."后的换行符
    
    while (getline(cin, line)) {
        s += line; // 将所有行连接成一个字符串
    }
    
    int n = s.length();
    
    // 修复3: 使用bool数组而非int数组，提升性能
    vector<bool> dp(n + 1, false);
    dp[0] = true; // 空串可以分解
    
    // 修复4: 关键性能优化
    // 利用题目约束：P中元素长度不超过10
    // 原代码复杂度O(n²)，优化后O(n*10) = O(n)
    for (int i = 0; i < n; i++) {
        if (dp[i]) {
            // 只检查长度1-10的子串，而不是所有可能的子串
            for (int len = 1; len <= 10 && i + len <= n; len++) {
                string substr = s.substr(i, len);
                if (judge(substr)) {
                    dp[i + len] = true;
                }
            }
        }
    }
    
    // 输出最长可分解前缀的长度
    for (int i = n; i >= 0; i--) {
        if (dp[i]) {
            cout << i << endl;
            return 0;
        }
    }
    
    return 0;
}