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










void solve() {
  int n, k;
  cin >> n >> k;
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  long best_max_so_far = a[n-1];
  for (int i = 0; i < n-1; i++) {
    // Consider making i the maximum
    long low = a[i], high = 300'000'000LL;
    while (low < high) {
      long goal = low + (high-low+1)/2;  // rounded up
      long ops_required = 0;
      for (int j = i; j < n; j++) {
        long ops_required_here = (goal - (j-i)) - a[j];
        if (ops_required_here <= 0)  break;
        ops_required += ops_required_here;
        if (j == n-1)  ops_required += INT_MAX;  // it's not possible
      }
      fprintf(stderr, "  requires %lld ops to make goal %lld\n", ops_required, goal);
      if (ops_required <= k) {
        low = goal;
      } else {
        high = goal-1;
      }
    }
    fprintf(stderr, "i=%d, best %lld maximum\n", i, low);
    best_max_so_far = max(best_max_so_far, low);
  }

  cout << best_max_so_far << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
