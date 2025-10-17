#include <bits/stdc++.h>

using namespace std;

#define int long long
inline int read()
{
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
int n, m;  //棋盘大小
int x, y;
int k;  //时间区间数目
//滑动距离最大值

vector<vector<int>> dp;
vector<vector<int>> dp1;
int flag[205][205];
/*
1:
dp[i][j]=dp[ii][j]+abs(i-ii)
*/

bool isright(int x, int y)
{
    if (!flag[x][y]) {
        return true;
    } else {
        return false;
    }
}
deque<int> de;  //递减

int ans = 0;
void f(int s, int d)
{
    
    if (d == 1) {
        
        for (int j = 1; j <= m; j++) {
            //枚举列
            de.clear();
            // de.push_back(n);
            for (int i = n; i >= 1; i--) {
                //枚举行
                if (!isright(i, j)) {
                    de.clear();
                    continue;
                }
             
                while (!de.empty() && abs(de.back() - de.front()) >= s) {
                    de.pop_front();
                }
                while (!de.empty() && dp[de.back()][j] + abs(de.back() - i) < dp[i][j]) {
                    de.pop_back();
                }
                de.push_back(i);

                if (!de.empty())
                    dp1[i][j] = dp[de.front()][j] + abs(de.front() - i);
                //新旧版本dp数组需要处理
              
                ans = max(ans, dp1[i][j]);
            }
        }
    }
    if (d == 2) {
        
        for (int j = 1; j <= m; j++) {
            //枚举列
            de.clear();
            // de.push_back(n);
            for (int i = 1; i <= n; i++) {
                //枚举行
                if (!isright(i, j)) {
                    de.clear();
                    continue;
                }
                
                while (!de.empty() && abs(de.back() - de.front()) >= s) {
                    de.pop_front();
                }
                while (!de.empty() && dp[de.back()][j] + abs(de.back() - i) < dp[i][j]) {
                    de.pop_back();
                }
                de.push_back(i);
                if (!de.empty())
                    dp1[i][j] = dp[de.front()][j] + abs(de.front() - i);
                //新旧版本dp数组需要处理
                
                ans = max(ans, dp1[i][j]);
            }
        }
    }
    if (d == 3) {
       
        for (int i = 1; i <= n; i++) {
            //枚举行
            de.clear();
            // de.push_back(n);
            for (int j = m; j >= 1; j--) {
                //枚举列
                if (!isright(i, j)) {
                    de.clear();
                    continue;
                }
              
                while (!de.empty() && abs(de.back() - de.front()) >= s) {
                    de.pop_front();
                }
                while (!de.empty() && dp[i][de.back()] + abs(de.back() - j) < dp[i][j]) {
                    de.pop_back();
                }
                de.push_back(j);
                if (!de.empty())
                    dp1[i][j] = dp[i][de.front()] + abs(de.front() - j);
                //新旧版本dp数组需要处理
               

                ans = max(ans, dp1[i][j]);
            }
        }
    }
    if (d == 4) {
        
        for (int i = 1; i <= n; i++) {
            //枚举行
            de.clear();
            // de.push_back(n);
            for (int j = 1; j <= m; j++) {
                //枚举列
                if (!isright(i, j)) {
                    de.clear();
                    continue;
                }
                
                while (!de.empty() && abs(de.back() - de.front()) >= s) {
                    de.pop_front();
                }
                while (!de.empty() && dp[i][de.back()] + abs(de.back() - j) < dp[i][j]) {
                    de.pop_back();
                }
                de.push_back(j);
                if (!de.empty())
                    dp1[i][j] = dp[i][de.front()] + abs(de.front() - j);
                //新旧版本dp数组需要处理
               

                ans = max(ans, dp1[i][j]);
            }
        }
    }
    dp = dp1;
    /*   for (int i = 1; i <= n;i++){
        for (int j = 1; j <= m;j++){
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }*/
}
//递归暴搜
signed main()
{
    cin >> n >> m >> x >> y >> k;
    dp.resize(n + 1);
    dp1.resize(n + 1);
    char temp;
    for (int i = 1; i <= n; i++) {
        dp[i].resize(m + 1, INT_MIN);
        dp1[i].resize(m + 1, INT_MIN);
        for (int j = 1; j <= m; j++) {
            cin >> temp;
            if (temp == 'x') {
                flag[i][j] = 1;
            }
        }
    }
    /*for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << flag[i][j] << ' ';
        }
        cout << endl;
    }*/

    dp[x][y] = 0;
    dp1[x][y] = 0;
    /*
        1
     3     4
        2
    */
    int tempa;
    int tempb;
    int d;
    int s;  //窗口范围
    for (int i = 1; i <= k; i++) {
        cin >> tempa >> tempb >> d;
        s = tempb - tempa + 1;
        // if(d==1) f(s,1,m,n,1)
        f(s, d);
    }
    cout << ans;
}