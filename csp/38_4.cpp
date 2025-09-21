#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 998244353
inline int read() {
  int x = 0, f = 1;      // x: 存储结果, f: 符号标志(1正数, -1负数)
  char ch = getchar();   // 读取第一个字符
  while (!isdigit(ch)) { // 跳过非数字字符
    if (ch == '-')
      f = -1;       // 遇到负号，设置符号为负
    ch = getchar(); // 继续读取下一个字符
  }
  while (isdigit(ch)) {    // 处理数字部分
    x = x * 10 + ch - '0'; // 将字符转换为数字并累加
    ch = getchar();        // 读取下一个字符
  }
  return x * f; // 返回结果（考虑符号）
}
string a = "ccf";
string b = "cspark";
int n;//字符串长度
int m;//#数量
int oth;
vector<int> temp;
vector<int> arr;//将邮编划分为几个区间，并记录每个区间的长度
vector<int> flag;//记录每个区间的状态
/*
0：能放a不能放b
1：都能放
*/
signed main() {
    cin >> n >> m;
    temp.resize(m + 2);
    temp[0] = 0;
    for (int i = 1; i <= m;i++){
        temp[i] = read();
    }
    temp[m + 1] = n + 1;
    //分为m+1个区域，只记录能放的区域
    //思路：只要找到一对a在前b在后的就行了。重复的问题到时再说
    for (int i = 1; i <= m + 1;i++)
    {
        int num =
            temp[i] - temp[i - 1] - 1;
        if(num<3){
            oth += num;
        }
        else if(num>=3&&num<6){
            flag.push_back(0);
            arr.push_back(num);
        }
        else{
            flag.push_back(1);
            arr.push_back(num);
        }

    }
    for (int i = 0; i < flag.size();i++){
        
    }
        return 0;
 }