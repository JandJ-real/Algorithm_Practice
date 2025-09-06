#include <bits/stdc++.h>
//寻找最大子段和

using namespace std;
int num;
int ans = INT_MIN;
int main() {
  cin >> num;
  int cursum = 0;//记录当前和
  int temp;
  //感觉思路很朴素
  while (num--) {
    cin >> temp;
    cursum = max(temp, cursum + temp);
    ans = max(ans, cursum);
  }
  cout << ans << endl;
  
}