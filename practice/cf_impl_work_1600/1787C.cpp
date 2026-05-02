#include <bits/stdc++.h>
using namespace std;
#define long long long


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












pair<long, long> get_extreme(long a, long s) {
  if (s >= a) {
    return {0, a};
  } else {
    return {s, a-s};
  }
}

void solve() {
  int n, s;
  cin >> n >> s;
  vector<long> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];

  pair<long, long> dp1 = {0, a[1]};
  pair<long, long> dp2 = {0, a[1]};

  for (int i = 2; i <= n-1; i++) {
    auto [xi, yi] = get_extreme(a[i], s);
    // xi, yi
    long new_dp1_x = dp1.first + dp1.second * xi;
    long new_dp2_x = dp2.first + dp2.second * xi;
    // yi, xi
    long new_dp1_y = dp1.first + dp1.second * yi;
    long new_dp2_y = dp2.first + dp2.second * yi;
    dp1 = {min(new_dp1_x, new_dp2_x), yi};
    dp2 = {min(new_dp1_y, new_dp2_y), xi};
  }

  // finally, multiply by a_n
  long dp1_ans = dp1.first + dp1.second * a[n];
  long dp2_ans = dp2.first + dp2.second * a[n];
  long ans = min(dp1_ans, dp2_ans);
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
