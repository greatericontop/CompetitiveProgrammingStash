#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG
//#define STRESSTESTING


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
  #pragma GCC diagnostic error "-Wall"
  #pragma GCC diagnostic error "-Wextra"
  #pragma GCC diagnostic error "-Wshadow"
  //#pragma GCC diagnostic error "-Wconversion"
  #pragma GCC diagnostic error "-Wfloat-equal"
  #pragma GCC diagnostic error "-Wduplicated-cond"
  #pragma GCC diagnostic error "-Wlogical-op"
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];
  a.push_back(1);  // dummy value

  vector<int> dp(8192, INT_MAX);  // possible values of current element
  dp[a[0]] = 0;

  // i, either zeroing it or xoring it (affecting i+1)
  for (int i = 0; i < n; i++) {
    vector<int> dp_new(8192, INT_MAX);
    for (int x = 0; x < 8192; x++) {
      if (dp[x] == INT_MAX)  continue;
      int cost = dp[x];
      // zero it, next elt unaffected
      dp_new[a[i+1]] = min(dp_new[a[i+1]], cost + (x != 0));
      // xor it
      if (x != 0) {
        int next_elt = a[i + 1] ^ x;
        dp_new[next_elt] = min(dp_new[next_elt], cost + 1);
      }
    }
    dp = dp_new;
    //PRINTVEC(dp);
  }

  int ans = INT_MAX;
  for (const auto& cst : dp)  ans = min(ans, cst);

  cout << ans << "\n";
}










void stresstest() {
  mt19937_64 rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count());
  //int n = 100'000;
  //...
  //solve();
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef STRESSTESTING
  fprintf(stderr, "Starting stresstest\n");
  static constexpr int RUNS = 100'000;
  for (int bundle = 1; true; bundle++) {
    for (int i = 0; i < RUNS; i++)  stresstest();
    fprintf(stderr, "Bundle %d, completed %d runs\n", bundle, RUNS);
  }
#else
  int t;
  cin >> t;
  while (t--)  solve();
#endif
  return 0;
}
