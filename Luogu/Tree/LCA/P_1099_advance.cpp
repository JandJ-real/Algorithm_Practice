#include <bits/stdc++.h>
/*
1.本解法n^3
2.位集优化弗洛伊德可到n^2/64
3.找一条直径，双指针枚举满足长度限制的路径 n^2
4.变更偏心距计算方式，使得可以用单调队列 可到n
*/
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
1. 找出一条直径，按顺序记录直径上的所有点
*/
int n, s;
int mid;  //中间节点
int ed;   //最后节点
int curmax;
vector<pair<int, int>> adj[305];
vector<vector<int>> edge(305,vector<int>(305,0));
int flag[305];
int fa[305];
vector<int> zhijing;

void dfs1(int cur, int deep) {
    flag[cur] = 1;
    if (deep > curmax) {
        //cout<<"cur:"<<cur<<' '<<"mid:"<<mid<<endl;
        mid = cur;
        curmax = deep;
    }
    for (size_t i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i].first;
        int d = adj[cur][i].second;
        if (!flag[next]) {
            dfs1(next, deep + d);
        }
    }
    return;
}
//遍历的同时建立父子关系
void dfs2(int cur, int deep) {
    //cout<<"dfs2"<<endl;
    flag[cur] = 1;
    if (deep > curmax) {
        //cout << "cur:" << cur << ' ' << "ed:" << ed << endl;
        ed = cur;
        curmax = deep;
    }
    for (size_t i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i].first;
        int d = adj[cur][i].second;
        if (!flag[next]) {
            fa[next] = cur;
            dfs2(next, deep + d);
        }
    }
    return;
}
int endans=INT_MAX;
signed main() {
    cin >> n >> s;
    int a, b, c;
    for (int i = 1; i < n; i++) {
        a = read();
        b = read();
        c = read();
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        edge[a][b]=c;
        edge[b][a]=c;
    }
    memset(flag, 0, sizeof(flag));
    dfs1(1, 0);
    fa[mid] = 0;
    //cout<<"biaozhi"<<endl;
    memset(flag, 0, sizeof(flag)), curmax = 0;
    dfs2(mid, 0);
    int temp = ed;
    while (fa[temp]) {
        zhijing.push_back(temp);
        temp = fa[temp];
    }
    zhijing.push_back(mid);
    //现在将一条直径上的所有点都存在了zhijing数组中
    // 2.取出所有满足长度限制的路径
    // 3.计算偏心距
    queue<pair<int, int>> que;
    
    int num = (int)zhijing.size();
     //cout<<mid<<' '<<ed<<endl;
    //cout<<endl;
    //for(int i=0;i<num;i++){
        //cout<<zhijing[i]<<endl;
    //}

    //cout<<endl;
    for (int i = 0; i < num; i++) {
        int dist=0;
        for (int j = i; j < num; j++) {
            dist+=edge[zhijing[j]][(j-1>=i)?zhijing[j-1]:zhijing[i]];
            //cout<<"dist:"<<dist<<endl;
            if (dist <= s) {
                //进行bfs
                int ans = 0;
                memset(flag, 0, sizeof(flag));
                for (int k = i; k <= j; k++) {
                    int temp = zhijing[k];
                    que.push({temp, 0});
                    flag[temp] = 1;
                }
                while (!que.empty()) {
                    int cur = que.front().first;
                    int curnum = que.front().second;
                    //flag[cur]=1;
                    ans = max(ans, curnum);
                    que.pop();
                    for (size_t u = 0; u < adj[cur].size(); u++) {
                        int next = adj[cur][u].first;
                        int shuzhi = adj[cur][u].second;if (!flag[next]) {
                            flag[next]=1;
                            que.push({next, curnum + shuzhi});
                        }
                    }
                }
                //cout<<ans<<endl;
                endans=min(endans,ans);
            }
        }
    }
    cout<<endans;
}