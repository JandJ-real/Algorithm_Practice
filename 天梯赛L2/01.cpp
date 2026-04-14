#include <bits/stdc++.h>
using namespace std;
#define int long long
//得：优先队列（大端树/小端树） reverse(begin,end)  next(迭代器)
//    从cnt的迭代方式可以看出两种方法的时间复杂度差异  O((e+v)logv)   O(n!)
//    dijstra算法适合非负权单源最短路 用优先队列可以到O((e+v)logv)
//以下为dfs暴力解法 时间复杂度为n的阶乘
/*
int cnt; //最短路的数量
int minlen = INT_MAX;
int ans; //救援队的最大数量
vector<int> bestpath;

//路径
void dfs(int cur, int len, int sum, vector<int> path, vector<bool> visited) {
    // cout<<cur<<' '<<len<<' '<<sum<<endl;

    path.push_back(cur);
    visited[cur] = 1;
    if (cur == d) {
        if (len < minlen) {
            //有更短的路，重新算
            cnt = 1;
            minlen = len;
            ans = sum;
            swap(bestpath, path);

        } else if (len == minlen) {
            //同为最短路，加计数并且比比优劣
            cnt++;
            if (sum > ans) {
                ans = sum;
                swap(bestpath, path);
            }
        }
        return;
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i].first;
        int step = adj[cur][i].second;
        if (!visited[next]) {
            dfs(next, len + step, sum + arr[next], path, visited);
        }
    }
    return;
}
*/
int n, m, s, d;
int arr[505];
vector<pair<int, int>> adj[505];
int rescue[505];   //最大救援数
int dist[505];     //最短距离
int prevnode[505]; //最大救援数的最短路径的前一个节点
int cnt[505];      //最短路数量
void dijstra() {
    fill(rescue, rescue + n, 0);
    fill(dist, dist + n, INT_MAX);
    fill(prevnode, prevnode + n, -1);
    fill(cnt, cnt + n, 0);

    dist[s] = 0;
    rescue[s] = arr[s];
    cnt[s] = 1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s}); //{距离，节点}
    while (!pq.empty()) {
        auto [curdist, u] = pq.top();
        pq.pop();
        //过期节点跳过？
        if (curdist > dist[u])
            continue;
        for (auto [v, w] : adj[u]) {
            int newdist = curdist + w;
            if (newdist < dist[v]) {
                //最短路，替换
                dist[v] = newdist;
                rescue[v] = rescue[u] + arr[v];
                cnt[v] = cnt[u]; //注意这里不是1
                prevnode[v] = u;
                //为何只在这里push
                pq.push({newdist, v});
            } else if (newdist == dist[v]) {
                if (rescue[u] + arr[v] > rescue[v]) {
                    rescue[v] = rescue[u] + arr[v];
                    prevnode[v] = u;
                }
                cnt[v]+=cnt[u];//注意这里不是++
            }
        }
    }
}
signed main() {
    cin >> n >> m >> s >> d;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int a, b, c;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    dijstra();
    cout << cnt[d] << ' ' << rescue[d] << endl;
    vector<int> path;
    int cur = d;
    while (cur != s) {
        path.push_back(cur);
        cur = prevnode[cur];
    }
    path.push_back(s);
    reverse(path.begin(), path.end());
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << *it;
        if (next(it) != path.end()) {
            cout << ' ';
        }
    }
}
