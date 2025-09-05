#include<bits/stdc++.h>

using namespace std;
int n;
int m;
int main(){
    cin >> n;
    vector<int> numbers(n);
    vector<int> prefix(n+1);
    for (int i = 0; i < n;i++){
        cin >> numbers[i];
    }
    //预处理
    prefix[0] = 0;
    for (int i = 1; i <=n;i++){
        prefix[i] = prefix[i - 1] + numbers[i-1];
    }
        cin >> m;
    vector<int> ans(m);
    int ta;
    int tb;
    for (int i = 0; i < m;i++){
        cin >> ta >> tb;
        ans[i] = prefix[tb ] - prefix[ta -1];
    }
    for (int i = 0; i < m;i++){
        cout << ans[i] << endl;
    }
}