#include <bits/stdc++.h>
using namespace std;

int main() {
  string str1;
  str1 = "ahh";
  string str2 = str1;
  reverse(str1.begin(), str1.end());
  cout << str1 << ' ' << str2;
}
