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
  string s, t;
  cin >> s >> t;

  if (s[0] != t[0] || s[n-1] != t[n-1]) {
    cout << "-1\n";
    return;
  }
  int ct = 0;

  char cur_block = s[0];
  int i = 0;
  for (int j = 1; j < n; j++) {
    if (s[j] != cur_block) {
      // block just ended
    }

  }

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
