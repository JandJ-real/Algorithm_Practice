#include<bits/stdc++.h>
using namespace std;
//每一个合法的pop和push序列对应一个结果，则只需搜索出所有结果即可
//栈为空，可push，栈不为空，可pop可push
int n;
int ans;
//push次数 栈中元素个数
void dfs(int pnum,int num){
     if(pnum==n){
        ans++;
        return;
     }

     if (pnum + 1 == n) {
       ans++;
     } else {
       dfs(pnum + 1, num + 1);
     }

     //非空
     if(num){
         dfs(pnum, num - 1);
     }
}
int main(){
    cin >> n;
    dfs(1, 1);
    cout << ans;
}

//栈的组合问题就是在计算卡特兰数，同类问题还有合法括号问题，n个结点的二叉搜索树问题