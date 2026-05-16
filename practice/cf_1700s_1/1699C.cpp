#include <bits/stdc++.h>
using namespace std;


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
#define long long long
#define pb push_back
using pairii = pair<int, int>;
using pairll = pair<long, long>;









constexpr static long MOD = 1'000'000'007;

void solve() {
  int n;
  cin >> n;
  vector<int> indexof(n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    indexof[a[i]] = i;
  }

  long ans = 1;
  int low = indexof[0];
  int high = indexof[0];
  for (int i = 1; i < n; i++) {
    int loc = indexof[i];
    if (loc < low) {
      low = loc;
    } else if (loc > high) {
      high = loc;
    } else {
      // inside
      long choices = (high - low + 1) - i;
      ans = (ans * choices) % MOD;
    }
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
