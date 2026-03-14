#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  vector<int> values(n+1);
  vector<int> difficulties(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> values[i];
    cin >> difficulties[i];
  }

  // Rec spec (hi cs381)
  // dp[i] = the best score you can get by processing tasks i...n, assuming a starting stamina of 1.
  // If your starting stamina is 0.6767 for example, then you have to multiply by 0.6767
  vector<double> dp(n+1);
  // base case: just do the last task
  dp[n] = (double) values[n];
  for (int i = n-1; i >= 1; i--) {
    // Ignore self
    double ignore_self = dp[i+1];
    // Do self
    double new_stamina_after_self = 1.0 - (difficulties[i]/100.0);
    double do_self = values[i] + new_stamina_after_self * dp[i+1];
    dp[i] = max(ignore_self, do_self);
  }

  cout << fixed << setprecision(12) << dp[1] << "\n";
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}