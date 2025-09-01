#include<bits/stdc++.h>
using namespace std;
int ans;
int m;
int n;
int main(){
cin>>n;
vector<int> arr(n);
for (int i = 0; i < n;i++){
    cin >> arr[i];
}

int cur = arr[0];
int ans = 1;

for (int i = 1; i < n;i++){
if(arr[i]>cur){
    ans++;
    cur = arr[i];
}
else{
    m = max(m, ans);
    cur=arr[i];
    ans = 1;
}
}

if(m==1)
    cout << 0;
    else
    cout << m;

}
