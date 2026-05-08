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
#define LONG(x) ((long) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  vector<vector<int>> indices(n+1);
  for (int i = 0; i < n; i++) {
    indices[a[i]].pb(i);
  }
  for (int x = 0; x <= n; x++) {
    fprintf(stderr, "%d:  indices ", x);
    for (int i : indices[x])  fprintf(stderr, "%d ", i);
    fprintf(stderr, "\n");
  }

  // Recursive spec: dp[i] = length of *completed* LIS of 1...i-1 (idea is then you can extend it)
  vector<int> dp(n+1, 0);
  for (int i = 0; i < n; i++) {
    if (i >= 1)  dp[i] = max(dp[i], dp[i-1]);
    int x = a[i];
    auto it = lower_bound(indices[x].begin(), indices[x].end(), i);
    assert(it != indices[x].end() && *it == i);
    int it_int = it - indices[x].begin();
    int it_new = it_int + x - 1;
    if (it_new < indices[x].size()) {
      int j = indices[x][it_new];
      dp[j+1] = max(dp[j+1], dp[i] + x);
      fprintf(stderr, "i=%d j=%d, setting dp[%d] = %d\n", i, j, j+1, dp[j+1]);
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
