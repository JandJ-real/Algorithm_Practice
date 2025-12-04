#include <bits/stdc++.h>
using namespace std;
#define int long long

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n;
int q;
//vector<int> arr;
map<int,int> mp;
signed main() {
    cin >> n;
    //arr.resize(n + 1);
    int temp;
for(int i=1;i<=n;i++){
    cin>>temp;
    mp[temp]=i;
}
    cin >> q;
while(q--){
    cin>>temp;
    cout<<mp[temp]<<endl;
}
}
