#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


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
  int n, m;
  long v;
  cin >> n >> m >> v;
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];
  vector<long> prefix(n);
  for (int i = 0; i < n; i++) {
    prefix[i] = a[i] + (i > 0 ? prefix[i-1] : 0);
  }

  // left_indices[0] = blank
  // left_indices[1] = index after rightmost of 1 satisfied alien
  vector<int> left_indices;
  left_indices.push_back(0);
  long total = 0;
  for (int i = 0; i < n; i++) {
    total += a[i];
    if (total >= v) {
      left_indices.push_back(i+1);
      total = 0;
    }
  }

  vector<int> right_indices;
  right_indices.push_back(n-1);
  total = 0;
  for (int i = n-1; i >= 0; i--) {
    total += a[i];
    if (total >= v) {
      right_indices.push_back(i-1);
      total = 0;
    }
  }

  long best = -1;
  for (int l = 0; l <= m; l++) {
    // l on the left and m-l on the right
    if (l >= (int)left_indices.size() || m-l >= (int)right_indices.size())  continue;
    int i = left_indices[l];
    int j = right_indices[m-l];
    if (i <= j) {
      long sum = prefix[j] - (i > 0 ? prefix[i-1] : 0);
      best = max(best, sum);
      fprintf(stderr, "l=%d, i=%d, j=%d, sum=%lld\n", l, i, j, sum);
    } else if (i == j+1) {
      best = max(best, 0LL);  //possible, but we get zero
    }
  }

  cout << best << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
