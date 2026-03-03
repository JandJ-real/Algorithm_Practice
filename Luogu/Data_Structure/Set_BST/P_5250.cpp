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
int m;
map<int, int> mp;
set<int> st;
int num;
signed main() {
    cin >> m;
    int a, b;
    while (m--) {
        cin >> a >> b;
        if (a == 1) {
            st.insert(b);
            if (!mp[b]) {
                mp[b] = 1;
                num++;
            } else {
                cout << "Already Exist" << endl;
            }
        } else {
            if (!num) {
                cout << "Empty" << endl;
                continue;
            }

            if (mp[b]) {
                st.erase(b);
                mp[b] = 0;
                num--;
                cout << b << endl;
                continue;
            } else {
                //没有符合的
                auto r = upper_bound(st.begin(), st.end(), b);
                auto l = r;
                if (l == st.begin()) {
                    st.erase(*r);
                    mp[*r] = 0;
                    num--;
                    cout << *r << endl;
                    continue;
                }
                l--;
                if (r == st.end()) {
                    st.erase(*l);
                    mp[*l] = 0;
                    num--;
                    cout << *l << endl;
                    continue;
                }
                // cout<<*r<<' '<<*l<<endl;
                if ((((*r) + (*l)) >> 1) < b) {
                    st.erase(*r);
                    mp[*r] = 0;
                    num--;
                    cout << *r << endl;
                } else {
                    st.erase(*l);
                    mp[*l] = 0;
                    num--;
                    cout << *l << endl;
                }
                /*
                                for (int i = 1;; i++) {
                    if (mp[b - i]) {
                        mp[b - i] = 0;
                        num--;
                        cout << b - i << endl;
                        break;
                    } else if (mp[b + i]) {
                        mp[b + i] = 0;
                        num--;
                        cout << b + i << endl;
                        break;
                    }
                }
                */
            }
        }
        // cout<<"num:"<<num<<endl;
        /*
                for(int x:st){
            cout<<x<<endl;
        }
        */
    }
}
