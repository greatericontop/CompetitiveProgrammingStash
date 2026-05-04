#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
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










constexpr static long INF = 1e18;
void solve() {
  int n;
  cin >> n;
  vector<long> k(n);
  for (int i = 0; i < n; i++)  cin >> k[i];
  vector<long> h_actual(n);
  for (int i = 0; i < n; i++)  cin >> h_actual[i];
  vector<long> h(n);
  for (int i = n - 1; i >= 0; i--) {
    h[i] = h_actual[i];
    if (i < n-1) {
      h[i] = max(h[i], h[i+1] - (k[i+1] - k[i]));
    }
  }
  PRINTVEC(h);

  vector<long> dp(n+1);
  dp[n] = 0;
  for (int i = n-1; i >= 0; i--) {
    if (i != 0 && h[i] > k[i] - k[i-1]) {
      // can't reset right before i
      dp[i] = INF;
    } else {
      dp[i] = INF;
      long h_cur = h[i];
      long cur = h_cur * (h_cur + 1) / 2;
      dp[i] = min(dp[i], cur + dp[i+1]);
      for (int j = i+1; j < n; j++) {
        long highest_here = h_cur + (k[j] - k[i]);
        dp[i] = min(dp[i], (highest_here)*(highest_here+1)/2 + dp[j+1]);
      }
      assert(dp[i] < INF);  //could just keep staying high
    }
  }
  PRINTVEC(dp);

  cout << dp[0] << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
