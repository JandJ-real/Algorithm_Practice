#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;//学生数
int p;//增加分数的次数
int ans;//最低分
signed main(){
    cin >> n >> p;
    vector<int> score(n);
    for (int i = 0; i < n;i++){
        cin >> score[i];
    }
    //差分
    vector<int> prefix(n);
    prefix[0] = score[0];
    for (int i = 1; i < n;i++){
        prefix[i] = score[i] - score[i - 1];
    }
    int x;
    int y;
    int deta;
    for (int i = 0; i < p;i++){
        cin >> x >> y >> deta;

        prefix[x - 1] += deta;

        if(y!=n)
        prefix[y] -= deta;
    }

    //找最小分
    int temp=prefix[0];
    ans = temp;
    for (int i = 1; i < n;i++){
        temp += prefix[i];
        ans = min(temp, ans);
    }
    cout << ans << endl;
}
