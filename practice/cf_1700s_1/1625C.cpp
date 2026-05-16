#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif
#define long long long
#define pb push_back
using pairii = pair<int, int>;
using pairll = pair<long, long>;










void solve() {
  int n, l, K;
  cin >> n >> l >> K;
  vector<int> d(n);  //coords
  for (int i = 0; i < n; i++)  cin >> d[i];
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  if (n == 1) {
    cout << l * a[0] << "\n";
    return;
  }

  // dp[i] [k: 0...k][j: 0...n-2]
  vector<vector<int>> dp(K+1, vector<int>(n-1));
  // base case: i=n-1
  for (int k = 0; k <= K; k++) {
    for (int j = 0; j <= n-2; j++) {
      // take the current speed sign
      dp[k][j] = (l - d[n-1]) * a[n-1];
      if (k >= 1) {
        // skip the current speed sign
        dp[k][j] = min(dp[k][j], (l - d[n-1]) * a[j]);
      }
      fprintf(stderr, "dp[n-1][k=%d][j=%d] = %d\n", k, j, dp[k][j]);
    }
  }

  vector<vector<int>> dp_new(K+1, vector<int>(n-1));
  for (int i = n-2; i >= 0; i--) {
    for (int k = 0; k <= K; k++) {
      for (int j = 0; j <= i; j++) {  //technically j <= i-1, but hacky for i=0
        // take the current speed sign
        dp_new[k][j] = (d[i+1] - d[i]) * a[i] + dp[k][i];
        if (k >= 1 && i != 0) {
          // skip the current speed sign if we are allowed to and not at the first one
          dp_new[k][j] = min(dp_new[k][j], (d[i+1] - d[i]) * a[j] + dp[k-1][j]);
        }
        fprintf(stderr, "dp[i=%d][k=%d][j=%d] = %d\n", i, k, j, dp_new[k][j]);
      }
    }
    swap(dp, dp_new);
    // dp_new will be overwritten
  }

  // answer = dp[i=0][k=K][j=hacky, 0]
  cout << dp[K][0] << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
