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










constexpr static long INF = LONG(1e18);

void solve() {
  int n, m;
  cin >> n >> m;
  vector<long> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  vector<long> a_prefix(n+1, 0);
  for (int i = 1; i <= n; i++)  a_prefix[i] = a_prefix[i-1] + a[i];
  vector<long> b(m+1);
  for (int i = 1; i <= m; i++)  cin >> b[i];


  vector<vector<long>> dp(n+2, vector<long>(m+1, INF));
  for (int k = 1; k <= m; k++) {
    dp[n+1][k] = 0;
  }
  for (int i = n; i >= 1; i--) {
    for (int k = m; k >= 1; k--) {
      if (k < m)  dp[i][k] = min(dp[i][k], dp[i][k+1]);

      // j points to after the segment we can delete
      int l = i, r = n+1;
      while (l < r) {
        int j = l + (r-l+1)/2;
        long sum = a_prefix[j-1] - a_prefix[i-1];
        if (sum <= b[k]) {
          l = j;
        } else {
          r = j-1;
        }
      }
      int j = l;
      if (j > i) {
        dp[i][k] = min(dp[i][k], dp[j][k] + (m-k));
      }  //if j==i, then potentially impossible (still INF)

      if (dp[i][k] > INF)  dp[i][k] = INF;
    }
  }

  if (dp[1][1] == INF) {
    cout << -1 << "\n";
  } else {
    cout << dp[1][1] << "\n";
  }



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
