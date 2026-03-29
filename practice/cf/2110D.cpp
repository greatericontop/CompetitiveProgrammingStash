#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op




constexpr static long HIGH = 100'000'000'000'000'000LL;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> b(n+1);
  for (int i = 1; i <= n; i++)  cin >> b[i];
  vector<vector<pair<int, int>>> adj(n+1);
  for (int i = 0; i < m; i++) {
    int u, v, cost;
    cin >> u >> v >> cost;
    adj[u].push_back({v, cost});
  }

  long low = 0, high = HIGH;
  while (low < high) {
    long guess = low + (high-low)/2;
    // dp[i] = most batteries you can have at node i
    vector<long> dp(n+1, -1);
    dp[1] = 0;
    for (int i = 1; i <= n; i++) {
      if (dp[i] == -1)  continue;
      long batteries_now = min(dp[i] + b[i], guess);
      for (auto [j, cost] : adj[i]) {
        if (batteries_now >= cost) {
          dp[j] = max(dp[j], batteries_now);
        }
      }
    }
    if (dp[n] != -1) {
      high = guess;
    } else {
      low = guess + 1;
    }
  }

  if (low >= HIGH) {
    cout << "-1\n";
  } else {
    cout << low << "\n";
  }
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}