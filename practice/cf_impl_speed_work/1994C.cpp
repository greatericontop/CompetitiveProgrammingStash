#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld, ", _x); \
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












constexpr static long INF = 1e15;
void solve() {
  int n;
  long x;
  cin >> n >> x;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  vector<long> prefix(n+2);
  for (int i = 1; i <= n; i++)  prefix[i] = prefix[i-1] + a[i];
  prefix[n+1] = INF;

  vector<long> dp(n+1);
  dp[n] = (a[n] > x) ? 1 : 0;  //eat only last mushroom
  for (int i = n-1; i >= 1; i--) {
    // bin search for smallest j s.t. prefix[j] > prefix[i-1]+x (aka range sum > x)
    auto it = upper_bound(prefix.begin(), prefix.end(), prefix[i-1]+x);
    int j = it - prefix.begin();
    assert(j >= i);
    if (j == n+1) {
      dp[i] = 0;  //can eat all remaining mushrooms and not reset to 0
    } else {
      if (j == n) {
        dp[i] = 1;
      } else {
        dp[i] = 1 + dp[j + 1];
      }
    }
  }
  PRINTVEC(dp);

  long ans = (((long)n) * (long)(n+1)) / 2;
  for (int i = 1; i <= n; i++)  ans -= dp[i];

  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
