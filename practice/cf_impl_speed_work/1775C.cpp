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










#define exp(x) (1LL << (x))
void solve() {
  long n, x;
  cin >> n >> x;

  for (int bit = 62; bit >= 0; bit--) {
    int n_set = (n >> bit) & 1;
    int x_set = (x >> bit) & 1;
    if (n_set == x_set) {
      continue;
    } else if (n_set == 0 && x_set == 1) {
      cout << -1 << "\n";
      return;
    } else {
      // bit+1 must be zero
      if ((n >> (bit + 1)) & 1) {
        cout << -1 << "\n";
        return;
      }
      // rest of x must be 0
      fprintf(stderr, "x=%lld, exp(bit)=%lld\n", x, exp(bit));
      if (x % exp(bit) != 0) {
        cout << -1 << "\n";
        return;
      }
      // ans = round up n to next exp(bit)
      long ans = (n / exp(bit)) * exp(bit);
      ans += exp(bit);
      assert(ans > n);
      cout << ans << "\n";
      return;
    }
  }

  // made it to end of loop = n and x are the same
  cout << n << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
