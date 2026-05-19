#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


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
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<long>> heights(n+1, vector<long>(m+1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> heights[i][j];
    }
  }
  vector<vector<bool>> snowy(n+1, vector<bool>(m+1, false));
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= m; j++) {
      snowy[i][j] = (s[j-1] == '1');
    }
  }
  long diff = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      diff += snowy[i][j] ? heights[i][j] : -heights[i][j];
    }
  }
  diff = abs(diff);
  fprintf(stderr, "diff: %lld\n", diff);


  vector<vector<int>> prefix_sums(n+1, vector<int>(m+1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      prefix_sums[i][j] = prefix_sums[i-1][j] + prefix_sums[i][j-1] - prefix_sums[i-1][j-1] + (1-2*snowy[i][j]);
    }
  }

  bool exists_nonzero_sum = false;
  int gcd_of_sums = 0;
  for (int i = k; i <= n; i++) {
    for (int j = k; j <= m; j++) {
      int sum = prefix_sums[i][j] - prefix_sums[i-k][j] - prefix_sums[i][j-k] + prefix_sums[i-k][j-k];
      fprintf(stderr, "sum @ %d, %d:  %d\n", i, j, sum);
      gcd_of_sums = gcd(gcd_of_sums, abs(sum));
      if (sum != 0)  exists_nonzero_sum = true;
    }
  }

  if (diff == 0 || (exists_nonzero_sum && diff % gcd_of_sums == 0)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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
