#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d, ", _x); \
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
















constexpr static long MOD = 998244353;
void solve() {
  int n;
  cin >> n;
  long extra;
  long amax = INT_MIN;
  vector<long> a(n+1);
  for (int i = 0; i <= n; i++) {
    if (i == 0) {
      cin >> extra;
    } else {
      cin >> a[i];
      amax = max(amax, a[i]);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (a[i] < amax) {
      long diff = (amax-1) - a[i];
      a[i] += diff;
      extra -= diff;
    }
    assert(a[i] == amax || a[i] == amax-1);
  }
  if (extra < 0) {
    cout << "0\n";
    return;
  }

  int k = 0;  //number with amax
  for (int i = 1; i <= n; i++) {
    if (a[i] == amax)  k++;
  }
  long l = extra;
  if (l > n-k)  l = n-k;

  long ans = 1;
  // ans = (l+k) * ... * (l+1) to place k
  //       (n-k)! for the rest
  for (int x = l+k; x > l; x--) {
    ans *= x;
    ans %= MOD;
  }
  for (int x = n-k; x > 0; x--) {
    ans *= x;
    ans %= MOD;
  }

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
