#pragma gcc optimize("Ofast")


#include <bits/stdc++.h>

using namespace std;
#define int long long

const int N = 2e5;
int dp[N+10];
vector<int> dv[N+10];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  dp[1] = 1;
  dp[0] = 1000000000;
  for (int i = 2; i <=n; i++) {
    for (int j=2*i; j<=n; j+=i) {
      dv[j].push_back(i);
    }
  }
  for (int i=2; i<=n; i++) {
    // cout << "id: " << i << endl;
    dp[i] = dp[i-1] + 1;
    for (auto a:dv[i]) {
      // cout << a << endl;
      dp[i] = min(dp[i], dp[a] + dp[i/a ]);
    }
    int mul = 1;
    int a = 0;
    for (int idx=0; idx<6; idx++ ) {
      int val = ((i/mul)%10 * mul);
      a += val;
      mul*=10;
      int b = i/mul;
      // cout << a << " " << b << " " << val << endl;
      if (val && a && b) dp[i] = min(dp[i], dp[a] + dp[b]);
    }
    for (int j=1; j<i; j++) {
      dp[i] = min(dp[i], dp[j] + dp[i-j]);
    }
  }
  cout << dp[n] << endl;
}