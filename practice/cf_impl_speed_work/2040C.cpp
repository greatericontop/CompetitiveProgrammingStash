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












long exp(int x) {
  if (x <= 60) {
    return 1LL << x;
  } else {
    return LLONG_MAX;  //we will always be less than / we will always choose the first option
  }
}
void solve() {
  int n;
  long k;
  cin >> n >> k;

  vector<int> perm(n+1);

  if (k > exp(n-1)) {
    cout << -1 << "\n";
    return;
  }

  int x = 1, y = n;
  for (int i = 1; i <= n-1; i++) {
    if (k > exp(n-i-1)) {
      perm[y] = i;
      y--;
      k -= exp(n-i-1);
    } else {
      perm[x] = i;
      x++;
    }
  }
  assert(x == y);
  perm[x] = n;

  for (int i = 1; i <= n; i++) {
    cout << perm[i] << " ";
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
