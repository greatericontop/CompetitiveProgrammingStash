#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG
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
  s += '$'; // placeholder
  t += '$';

  if (s[0] != t[0] || s[n-1] != t[n-1]) {
    cout << "-1\n";
    return;
  }
  long ct = 0;

  int i = 0;
  int j = 0;
  for (int block = 0; true; block++) {
    if ((i == n && j != n) || (i != n && j == n)) {
      // unequal blocks
      cout << "-1\n";
      return;
    }
    if (i == n && j == n) {
      break;
    }

    int i0 = i, j0 = j;
    assert(s[i] == t[j]);
    while (s[i] == s[i+1])  i++;
    while (t[j] == t[j+1])  j++;
    i++; j++; // now they point to the next block

    //int ct0 = ct;
    // Copy s to t
    if (i < j) {
      ct += (long) (j - i);
    }
    if (j0 < i0) {
      ct += (long) (i0 - j0);
    }
    fprintf(stderr, "block %d: i0=%d, j0=%d, i=%d, j=%d, count += %d\n", block, i0, j0, i, j, ct - ct0);
  }

  cout << ct << "\n";

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
