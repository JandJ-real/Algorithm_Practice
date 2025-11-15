#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 100005;
const int MAXE = MAXN << 1;  // 因为是无向图，边是2倍
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

// ---------- 全局变量 ----------
int n, m, r, MOD;
int arr[MAXN], newarr[MAXN];
int siz[MAXN], son[MAXN], Fa[MAXN], deep[MAXN];
int dfn[MAXN], top[MAXN];
int tim = 0;

// ---------- 链式前向星 ----------
int head[MAXN], to[MAXE], nxt[MAXE], tot;
inline void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

// ---------- 非递归 dfs1 ----------
void dfs1_iter(int root) {
    struct Frame {
        int u, fa, state, dep;
    };
    stack<Frame> st;
    st.push({root, 0, 0, 0});

    while (!st.empty()) {
        auto [u, fa, state, dep] = st.top();
        st.pop();
        if (state == 0) {
            Fa[u] = fa;
            deep[u] = dep;
            siz[u] = 1;
            son[u] = 0;
            st.push({u, fa, 1, dep});
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa)
                    continue;
                st.push({v, u, 0, dep + 1});
            }
        } else {
            int maxson = 0;
            siz[u] = 1;  // 防止重复累加
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == Fa[u])
                    continue;
                siz[u] += siz[v];
                if (siz[v] > maxson) {
                    maxson = siz[v];
                    son[u] = v;
                }
            }
        }
    }
}

// ---------- 非递归 dfs2 ----------
void dfs2_iter(int root) {
    struct Frame {
        int u, topNode, state;
    };
    stack<Frame> st;
    st.push({root, root, 0});

    while (!st.empty()) {
        auto [u, tp, state] = st.top();
        st.pop();

        if (state == 0) {
            top[u] = tp;
            dfn[u] = ++tim;
            newarr[tim] = arr[u];

            st.push({u, tp, 1});
            if (son[u])
                st.push({son[u], tp, 0});
        } else {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == Fa[u] || v == son[u])
                    continue;
                st.push({v, v, 0});
            }
        }
    }
}

// ---------- 线段树 ----------
struct segmenttree {
    struct node {
        int lazy, sum;
    } t[4 * MAXN];

    void push_up(int p) {
        t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    }

    void push_down(int p, int l, int r) {
        if (!t[p].lazy)
            return;
        int mid = (l + r) >> 1;
        t[p << 1].lazy += t[p].lazy;
        t[p << 1 | 1].lazy += t[p].lazy;
        t[p << 1].sum += (mid - l + 1) * t[p].lazy;
        t[p << 1 | 1].sum += (r - mid) * t[p].lazy;
        t[p].lazy = 0;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            t[p].sum = newarr[l] % MOD;
            t[p].lazy = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        push_up(p);
    }

    void add(int p, int l, int r, int L, int R, int x) {
        if (L <= l && r <= R) {
            t[p].lazy += x;
            t[p].sum += (r - l + 1) * x;
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid)
            add(p << 1, l, mid, L, R, x);
        if (R > mid)
            add(p << 1 | 1, mid + 1, r, L, R, x);
        push_up(p);
    }

    int getsum(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R)
            return t[p].sum % MOD;
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        int ans = 0;
        if (L <= mid)
            ans += getsum(p << 1, l, mid, L, R);
        if (R > mid)
            ans += getsum(p << 1 | 1, mid + 1, r, L, R);
        return ans % MOD;
    }
} seg;

// ---------- 主函数 ----------
signed main() {
    n = read();
    m = read();
    r = read();
    MOD = read();
    for (int i = 1; i <= n; i++) arr[i] = read();
    for (int i = 1; i < n; i++) {
        int a = read(), b = read();
        add_edge(a, b);
        add_edge(b, a);
    }

    dfs1_iter(r);
    dfs2_iter(r);
    seg.build(1, 1, n);

    while (m--) {
        int op = read();
        if (op == 1) {
            int x = read(), y = read(), z = read();
            while (top[x] != top[y]) {
                if (deep[top[x]] < deep[top[y]])
                    swap(x, y);
                seg.add(1, 1, n, dfn[top[x]], dfn[x], z);
                x = Fa[top[x]];
            }
            if (deep[x] > deep[y])
                swap(x, y);
            seg.add(1, 1, n, dfn[x], dfn[y], z);
        } else if (op == 2) {
            int x = read(), y = read();
            int ans = 0;
            while (top[x] != top[y]) {
                if (deep[top[x]] < deep[top[y]])
                    swap(x, y);
                ans += seg.getsum(1, 1, n, dfn[top[x]], dfn[x]);
                ans %= MOD;
                x = Fa[top[x]];
            }
            if (deep[x] > deep[y])
                swap(x, y);
            ans += seg.getsum(1, 1, n, dfn[x], dfn[y]);
            cout << ans % MOD << "\n";
        } else if (op == 3) {
            int x = read(), z = read();
            seg.add(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, z);
        } else if (op == 4) {
            int x = read();
            cout << seg.getsum(1, 1, n, dfn[x], dfn[x] + siz[x] - 1) % MOD << "\n";
        }
    }
}
