#include<bits/stdc++.h>
using namespace std;

int n;

int main(){
    cin >> n;
    //注意要在输入完n后建立向量
    vector<int> arr(n);
    //若无比该元素大的则记为零，故ans数组初始化为零
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    //以上为输入
    // 单调栈，存储序号
    stack<int> s;


    //以下过程导致的初始状态：第一个元素入栈
    //之后：先和栈顶元素比较，若小于等于栈顶则直接存入栈，若大于栈顶则计入ans数组并弹出栈顶元素，并依次与栈中其他元素比较（因为并且因此维持了栈中元素的单调性）
    for (int i = 0; i < n; i++) {
      while ((!s.empty()) && arr[s.top()] < arr[i]) {
        ans[s.top()] = i + 1;
        s.pop();
    }
    s.push(i);
}

    //以下为输出
for (int i = 0; i < n;i++){
    cout << ans[i] << ' ';
}
}