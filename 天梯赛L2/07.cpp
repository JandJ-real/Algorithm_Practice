#include <bits/stdc++.h>
using namespace std;
#define int long long
//抽象化问题 转成并查集 抓住家族的本质，不被父母干扰
//merge的时机，为什么不在每行输入后直接合并，而是先存起来
//fa[0]的bug : 因为全局数组默认为0，这会让原来的逻辑认为只是一个独立的家族
//%04lld
//我喜欢这个题

//两个父亲节点的并查集？
//父母不重要，都是家庭中的一个人，而为了方便，把编号小的定为根节点
/*
n
编号 父 母 k 孩子1 ... 孩子k 房产套数 总面积

家庭成员的最小编号 家庭人口数 人均房产套数 人均房产面积
其中人均值要求保留小数点后3位。家庭信息首先按人均面积降序输出，若有并列，则按成员编号的升序输出。
*/
/*
10
6666 5551 5552 1 7777 1 100
1234 5678 9012 1 0002 2 300
8888 -1 -1 0 1 1000
2468 0001 0004 1 2222 1 500
7777 6666 -1 0 2 300
3721 -1 -1 1 2333 2 150
9012 -1 -1 3 1236 1235 1234 1 100
1235 5678 9012 0 1 50
2222 1236 2468 2 6661 6662 1 300
2333 -1 3721 3 6661 6662 6663 1 100
*/
/*
3
8888 1 1.000 1000.000
0001 15 0.600 100.000
5551 4 0.750 100.000
*/
int fa[10005];
int housenum[10005];
int area[10005];
int peoplenum[10005];
int find(int a) {
    if (a == fa[a]) {
        return a; //自己就是根节点
    }
    return fa[a] = find(fa[a]);
}
void merge(int a, int b) {
    if (find(a) == find(b)) {
        return;
    }
    int aa = find(a), bb = find(b);
    if (aa > bb) {
        //选择更小的作为根节点
        swap(aa, bb);
    }
    fa[bb] = aa;
    housenum[aa] += housenum[bb];
    area[aa] += area[bb];
    peoplenum[aa] += peoplenum[bb];
    return;
}
int n;
struct nod {
    int root;
    int peoplenum;
    double house_num;
    double areanum;
};
vector<nod> arr;
vector<int> ship[10005];
bool mycompare(nod a, nod b) {
    if (a.areanum > b.areanum) {
        return true;
    }
    if (a.areanum == b.areanum && a.root < b.root) {
        return true;
    }
    return false;
}
signed main() {
    cin >> n;
    int tid, dad, mum, k, son, house, are;
    fa[0]=-1;//真正运行才能想到的bug
    for (int i = 1; i <= n; i++) {
        cin >> tid >> dad >> mum >> k;
        fa[tid] = tid;
        peoplenum[tid] = 1;
        for (int j = 1; j <= k; j++) {
            cin >> son;
            fa[son] = son;
            peoplenum[son] = 1;
            ship[tid].push_back(son);
        }
        if (dad != -1) {
            fa[dad] = dad;
            peoplenum[dad] = 1;
            ship[tid].push_back(dad);
        }
        if (mum != -1) {
            fa[mum] = mum;
            peoplenum[mum] = 1;
            ship[tid].push_back(mum);
        }
        cin >> house >> are;
        housenum[tid] += house, area[tid] += are;
    }
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < (int)ship[i].size(); j++) {
            int x = ship[i][j];
            merge(i, x);
        }
    }
    for (int i = 0; i < 10000; i++) {
        if (fa[i] == i) {
            //找到了一个家族
            arr.push_back({i, peoplenum[i],
                           (double)(housenum[i]) / peoplenum[i],
                           (double)area[i] / peoplenum[i]});
        }
    }
    sort(arr.begin(), arr.end(), mycompare);
    cout<<arr.size()<<endl;
    for (auto it : arr) {
        printf("%04lld", it.root);
        cout << ' ';
        cout << it.peoplenum << ' ';
        printf("%.3f", it.house_num);
        cout << ' ';
        printf("%.3f", it.areanum);
        cout << endl;
    }
}