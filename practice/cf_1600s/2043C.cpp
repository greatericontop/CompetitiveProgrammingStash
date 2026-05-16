#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld, ", _x); \
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
  vector<long> a(n);
  int special;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] != 1 && a[i] != -1)  special = i;
  }

  set<long> valid;
  valid.insert(0);

  // left
  if (special != 0) {
    long prefix_l = 0;
    long prefix_r = 0;
    long reachable_l = 0;
    long reachable_r = 0;
    long prefix_sum = 0;
    for (int i = 0; i < special; i++) {
      prefix_sum += a[i];
      reachable_l = min(reachable_l, prefix_sum-prefix_r);
      reachable_r = max(reachable_r, prefix_sum-prefix_l);

      prefix_l = min(prefix_l, prefix_sum);
      prefix_r = max(prefix_r, prefix_sum);
    }
    assert(reachable_l <= reachable_r);
    assert(reachable_r - reachable_l <= 600'000);
    for (long x = reachable_l; x <= reachable_r; x++) {
      valid.insert(x);
    }
  }
  if (special != n-1) {
    long prefix_l = 0;
    long prefix_r = 0;
    long reachable_l = 0;
    long reachable_r = 0;
    long prefix_sum = 0;
    for (int i = special+1; i < n; i++) {
      prefix_sum += a[i];
      reachable_l = min(reachable_l, prefix_sum-prefix_r);
      reachable_r = max(reachable_r, prefix_sum-prefix_l);

      prefix_l = min(prefix_l, prefix_sum);
      prefix_r = max(prefix_r, prefix_sum);
    }
    assert(reachable_l <= reachable_r);
    assert(reachable_r - reachable_l <= 600'000);
    for (long x = reachable_l; x <= reachable_r; x++) {
      valid.insert(x);
    }
  }

  // arrays containing special
  long lmin = 0, lmax = 0;
  long lprefix = 0;
  for (int i = special-1; i >= 0; i--) {
    lprefix += a[i];
    lmin = min(lmin, lprefix);
    lmax = max(lmax, lprefix);
  }
  long rmin = 0, rmax = 0;
  long rprefix = 0;
  for (int i = special+1; i < n; i++) {
    rprefix += a[i];
    rmin = min(rmin, rprefix);
    rmax = max(rmax, rprefix);
  }
  long low = a[special] + lmin + rmin;
  long high = a[special] + lmax + rmax;
  assert(low <= high);
  assert(high - low <= 1'200'000);
  for (long x = low; x <= high; x++) {
    valid.insert(x);
  }

  cout << valid.size() << "\n";
  for (long x : valid) {
    cout << x << " ";
  }
  cout << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
