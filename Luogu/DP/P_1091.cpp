#include <bits/stdc++.h>
using namespace std;
//最多留下几位同学，可以满足条件
int n;
int ans;
signed main() {
cin>>n;
vector<int> arr(n+1);
for(int i=1;i<=n;i++){
    cin >> arr[i];
}

vector<int> dpl(n + 1, 1);
//以i结尾
vector<int> dpr(n + 1, 1);
for(int i=2;i<=n;i++){
    for(int j=1;j<=i-1;j++){
        if(arr[i]>arr[j]){
            dpl[i] = max(dpl[i], dpl[j] + 1);
        }
    }

}
for (int i = n-1; i >= 1; i--) {
  for (int j = n; j >= i + 1; j--) {
    if (arr[i] > arr[j]) {
      dpr[i] = max(dpr[i], dpr[j] + 1);
    }
  }
 
}
for(int i=1;i<=n;i++){
    ans = max(ans, dpl[i] + dpr[i] - 1);
}
cout << n - ans;
}