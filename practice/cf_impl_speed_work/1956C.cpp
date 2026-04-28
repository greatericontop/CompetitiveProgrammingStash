#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d %d, ", _x.first, _x.second); \
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
  int max_sum = 0;
  for (int i = 1; i <= n; i++) {
    max_sum += i * (2*i-1);
  }
  cout << max_sum << " " << (2*n) << "\n";

  for (int i = n; i >= 1; i--) {
    cout << 1 << " " << i << " ";
    for (int j = 1; j <= n; j++) {
      cout << j << " ";
    }
    cout << "\n";
    cout << 2 << " " << i << " ";
    for (int j = 1; j <= n; j++) {
      cout << j << " ";
    }
    cout << "\n";
  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
