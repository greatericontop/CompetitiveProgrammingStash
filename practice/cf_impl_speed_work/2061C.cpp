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













#define truths first
#define ways second
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  pair<int, long> lastTruth = {0, 1};
  pair<int, long> lastLie = {0, 0};
  for (int i = 0; i < n; i++) {
    int x = i - a[i];  //if a[i] is truth, then must be x truths
    pair<int, long> curTruth = {x+1, 0};
    pair<int, long> curLie = {-1, 0};

    // lastLie + this one is truth -> curTruth
    if (lastLie.truths == x) {
      curTruth.ways += lastLie.ways;
    }
    // lastTruth + this one is truth -> curTruth
    if (lastTruth.truths == x) {
      curTruth.ways += lastTruth.ways;
    }
    // lastTruth + this one is lie -> curLie
    curLie.truths = lastTruth.truths;
    curLie.ways = lastTruth.ways;

    curTruth.ways %= 998244353LL;
    curLie.ways %= 998244353LL;
    lastTruth = curTruth;
    lastLie = curLie;

    fprintf(stderr, "i=%d, truth=(%d, %lld), lie=(%d, %lld)\n", i, lastTruth.truths, lastTruth.ways, lastLie.truths, lastLie.ways);
  }

  long ans = lastTruth.ways + lastLie.ways;
  ans %= 998244353LL;
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
