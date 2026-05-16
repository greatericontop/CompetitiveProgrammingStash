#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


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










void solve() {
  int n;
  cin >> n;
  vector<double> X(n);
  for (int i = 0; i < n; i++)  cin >> X[i];
  vector<double> T(n);
  for (int i = 0; i < n; i++)  cin >> T[i];

  double low = 0.0, high = 100'000'000.0;
  while ((high - low)/max(1.0, low) > 1e-8) {
    double x = low + (high-low)/2.0;
    double left_bottleneck = -1.0;
    double right_bottleneck = -1.0;
    for (int i = 0; i < n; i++) {
      double cost = T[i] + abs(X[i] - x);
      if (X[i] < x) {
        left_bottleneck = max(left_bottleneck, cost);
      } else {
        right_bottleneck = max(right_bottleneck, cost);
      }
    }
    if (left_bottleneck < right_bottleneck) {
      // right bottleneck is worse, so going left is never good
      low = x;
    } else {
      high = x;
    }
  }

  cout << fixed << setprecision(12) << low + (high-low)/2.0 << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
