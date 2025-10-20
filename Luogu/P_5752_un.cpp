#include <bits/stdc++.h>

using namespace std;
#define int long long
inline int read() {
    int x = 0, f = 1;     // x: 存储结果, f: 符号标志(1正数, -1负数)
    char ch = getchar();  // 读取第一个字符

    while (!isdigit(ch)) {  // 跳过非数字字符
        if (ch == '-')
            f = -1;      // 遇到负号，设置符号为负
        ch = getchar();  // 继续读取下一个字符
    }

    while (isdigit(ch)) {       // 处理数字部分
        x = x * 10 + ch - '0';  // 将字符转换为数字并累加
        ch = getchar();         // 读取下一个字符
    }

    return x * f;  // 返回结果（考虑符号）
}
/*
如何模拟分割
原：1，1   8，8
1，1 8，3
1，4  8，8   -  1，4  2，8   =   3，4   8，8
3，4   4，8  -  3，6   4，8    3，4  4，5

a ,b   c,d -  a,b  k,d =  k+1,b  c,d
a ,b   c,d -  a,b  c,k =  a,k+1  c,d
*/
int n;

int prefix[9][9];
vector<double> remem;
double ans=DBL_MAX;
double calc(vector<double> remem){
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=remem[i];
    }
    double ba=((double)(sum))/n;
    double s2sum=0;
    for(int i=0;i<n;i++){
        //cout<<remem[i]<<' ';
        s2sum+=(remem[i]-ba)*(remem[i]-ba);
    }
    //cout<<endl;
    double s2=s2sum/n;
    return round(sqrt(s2)*1000.0)/1000.0;
}
void f(int cur,int lx,int ly,int rx,int ry){
    int a,b,c,d;
  //cout<<"cur:"<<cur<<endl;
  if (cur == n-1) {
      remem[n - 1] = prefix[rx][ry] - prefix[lx - 1][ry] - prefix[rx][ly - 1] + prefix[lx - 1][ly - 1];
      ans = min(ans, calc(remem));
      return;
  }
for(int i=lx;i<=rx-1;i++){
a=lx,b=ly,c=i,d=ry;
    remem[cur]=prefix[c][d]-prefix[a-1][d]-prefix[c][b-1]+prefix[a-1][b-1];
    f(cur + 1, i + 1, ly, rx,ry);
    a=i+1,b=ly,c=rx,d=ry;
    remem[cur] = prefix[c][d] - prefix[a - 1][d] - prefix[c][b - 1] + prefix[a - 1][b - 1];
    f(cur + 1, lx, ly, i, ry);
}
for(int i=ly;i<=ry-1;i++){
    a=lx,b=ly,c=rx,d=i;
    remem[cur] = prefix[c][d] - prefix[a - 1][d] - prefix[c][b - 1] + prefix[a - 1][b - 1];
    f(cur + 1, lx, i + 1, rx, ry);
    a=lx,b=i+1,c=rx,d=ry;
    remem[cur] = prefix[c][d] - prefix[a - 1][d] - prefix[c][b - 1] + prefix[a - 1][b - 1];
    f(cur + 1, lx, ly, rx, i);
}

}
signed main() {
    cin >> n;
    remem.resize(n);
    int temp;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            temp=read();
            prefix[i][j] = prefix[i][j - 1] + temp;
        }
    }
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            prefix[j][i] += prefix[j - 1][i];
        }
    }
    f(0,1,1,8,8);
    cout<<ans;

    /*
a,b   c,d
c,d   -  a-1,d   -  c,b-1    +   a-1,b-1  

*/
    /*for (int i = 0; i <= 8; i++) {
        for (int j = 0; j <= 8; j++) {
            cout<<prefix[i][j]<<' ';
        }
        cout<<endl;
    }*/
}