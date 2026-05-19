#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECL(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:   ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECP(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%d %d],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECPL(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%lld %lld],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }










void solve() {
  int n, K;
  cin >> n >> K;
  vector<long> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  vector<long> sums(n+1);
  sums[0] = 0;
  for (int i = 1; i <= n; i++)  sums[i] = sums[i-1] + a[i];

  vector<vector<long>> dp(n+1, vector<long>(K+1));
  for (int j = 0; j <= K; j++)  dp[0][j] = 0;
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k <= K; k++) {
      // solve for dp[i][k]
      // k_before = k
      dp[i][k] = dp[i-1][k] + a[i];
      long range_min = a[i];
      for (int k_before = k+1; k_before <= K; k_before++) {
        int window_size = k_before - k + 1;
        if (window_size > i)  break;
        range_min = min(range_min, a[i-window_size+1]);
        long dp_here = dp[i-window_size][k_before] + range_min * window_size;
        dp[i][k] = min(dp[i][k], dp_here);
      }
    }
  }

  long ans = accumulate(dp[n].begin(), dp[n].end(), LONG(1e18), [](long acc, long x) { return min(acc, x); });
  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
