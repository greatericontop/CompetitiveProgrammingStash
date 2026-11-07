#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, s, b, m;
string str;
int ans = -INT_MIN, pos=-1;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> s >> b >> m;
  cin >> str;
  for (int i = 1; i <= s;i++) {
    int cur_ans = b;
    for (int j = 1; j <= n;j++) {
      char c;
      int bet;
      cin >> c >> bet;
      if (cur_ans - bet < m) {
        continue;
      }
      if (c == str[j-1]) {
        cur_ans += bet;
      } else {
        cur_ans -= bet;
      }
    }
    if (ans < cur_ans) {
      ans = cur_ans;
      pos = i;
    }
  }
  cout << pos <<' ' << ans << endl;
}