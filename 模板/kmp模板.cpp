#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
string a,sub;
cin >> a>>sub;
int lena = a.length();
/*vector<size_t> ans;
size_t temp=a.find(sub);

while(temp!=string::npos){
    ans.push_back(temp);
    temp = a.find(sub, temp + 1);
}

for(size_t pos : ans){
    cout << pos + 1 << endl;
}
*/
//最长border长度实际上是在对字符串sub构建next数组
int len_sub = sub.length();
vector<int> next(len_sub);
next[0]=0;

for (int j = 0, i = 1; i < len_sub;i++){
     while(j>0&&sub[i]!=sub[j]) j=next[j-1];
     if(sub[i]==sub[j]) j++;
     next[i] = j;
}

// 使用KMP算法进行匹配
int j = 0;                 // 重置j，用于跟踪模式串的匹配位置
vector<int> positions; // 存储所有匹配位置

for (int i = 0; i < lena; i++) {
  while (j > 0 && a[i] != sub[j]) {
    j = next[j - 1]; // 匹配失败，智能回退
  }
  if (a[i] == sub[j]) {
    j++;
  }
  if (j == len_sub) {
    // 找到匹配，记录位置（从1开始计数）
    positions.push_back(i - len_sub + 2);
    j = next[j - 1]; // 继续寻找下一个可能的匹配
  }
}

// 输出所有匹配位置
for (int pos : positions) {
  cout << pos << endl;
}

for (int i = 0; i < len_sub;i++){
    cout << next[i] << ' ';
}
}
//注意：大多数情况下直接使用find函数寻找字串位置更高效也更方便