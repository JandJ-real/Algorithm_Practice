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
int n;
// 1号结点为根节点
vector<int> adj[105];
//求深度
int ans1 = 0;
int flag[105];
void deep(int cur, int curdeep) {
    ans1 = max(ans1, curdeep);
    flag[cur] = 1;
    for (size_t i = 0; i < adj[cur].size(); i++) {
        if (!flag[adj[cur][i]])
            deep(adj[cur][i], curdeep + 1);
    }
    return;
}
//宽度
int ans2 = 1;
//奇怪的距离:将向根方向的边赋值为2，向叶的边赋值为1
int dist[105][105];

signed main() {
    cin >> n;
    int u, v;
    for (int i = 1; i < n; i++) {
        u = read();
        v = read();
        adj[u].push_back(v);
        adj[v].push_back(u);
        
    }
    int ta,tb;
    cin>>ta>>tb;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = 1000000;
            dist[j][i] = 1000000;
        }
    }


    memset(flag, 0, sizeof(flag));
    deep(1, 1);
    cout << ans1 << endl;

    memset(flag, 0, sizeof(flag));
    queue<int> que;
    queue<int> que2;
    que.push(1);
    flag[1] = 1;
    while (!que.empty() || !que2.empty()) {
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            for (size_t i = 0; i < adj[cur].size(); i++) {
                if (!flag[adj[cur][i]]) {
                    que2.push(adj[cur][i]);
                    dist[cur][adj[cur][i]]=1;
                    dist[adj[cur][i]][cur]=2;
                    flag[adj[cur][i]] = 1;
                    // cout<<adj[cur][i]<<endl;
                }
            }
        }
        ans2 = max(ans2, (int)que2.size());
        // cout<<(int)que2.size()<<endl;
        swap(que, que2);
    }
    cout << ans2 << endl;


 
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }
    //另外的初始化在bfs中顺便进行
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        for(int k=1;k<=n;k++){
            dist[i][j]=min(dist[i][k]+dist[k][j],dist[i][j]);
        }
    }
}
cout<<dist[ta][tb]<<endl;

//另外第三问还可以用最近公共祖先(LCA)
/*
eg:求 a 与 b 的公共祖先：
1.不停的给a找爸爸 直到根节点
2.找的过程中 记录已经走过的结点，例如插入到unordered_set中
3.再不停的给b找爸爸，每次都判断 是否在1步骤中走过
4.第一个重合的结点 就是 LCA
*/
}