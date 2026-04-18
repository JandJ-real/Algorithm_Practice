#include <bits/stdc++.h>
using namespace std;
#define int long long
int n; // 2~1e5
vector<int> arr;
int ans;
/*
两端分别是一条入口（Entrance）轨道和一条出口（Exit）轨道，它们之间有N条平行的轨道。每趟列车从入口可以选择任意一条轨道进入，最后从出口离开。在图中有9趟列车，在入口处按照{8，4，2，5，3，9，1，6，7}的顺序排队等待进入。如果要求它们必须按序号递减的顺序从出口离开，则至少需要多少条平行铁轨用于调度？
*/
//下降子序列数量的最少值
//即最长上升子序列的长度
//我真是个天才
signed main() {
    cin >> n;
    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        auto it = upper_bound(arr.begin(), arr.end(), x);
        if (it != arr.end()) {
            *it = x;
        } else {
            arr.push_back(x);
        }
    }
    cout << arr.size();
    return 0;
}