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










void solve_recursively(const vector<int>& valid_nums) {
  if (valid_nums.size() == 1) {
    cout << "! " << valid_nums[0] << endl;
    return;
  }
  if (valid_nums.size() == 2) {
    cout << "? " << valid_nums[0] << " " << valid_nums[1] << endl;
    int x; cin >> x; assert(x != -1);
    if (x == 1) {
      cout << "! " << valid_nums[0] << endl;
    } else {
      assert(x == 2);
      cout << "! " << valid_nums[1] << endl;
    }
    return;
  }

  vector<int> next_valid_nums;
  for (int i = 0; i < (int)valid_nums.size(); i += 4) {
    cout << "? " << valid_nums[i] << " " << valid_nums[i+2] << endl;
    int x; cin >> x; assert(x != -1);
    int c1, c2;
    if (x == 1) {
      // i beat i+2, so it's between i and i+3
      c1 = i; c2 = i+3;
    } else if (x == 2) {
      // i+2 beat i, so it's between i+2 and i+1
      c1 = i+2; c2 = i+1;
    } else {
      // betweeen i+1 and i+3
      c1 = i+1; c2 = i+3;
    }
    cout << "? " << valid_nums[c1] << " " << valid_nums[c2] << endl;
    cin >> x; assert(x != -1);
    if (x == 1) {
      next_valid_nums.push_back(valid_nums[c1]);
    } else {
      assert(x == 2);
      next_valid_nums.push_back(valid_nums[c2]);
    }
  }
  solve_recursively(next_valid_nums);
}


void solve() {
  int k;
  cin >> k;
  int n = 1 << k;
  vector<int> valid_nums;
  for (int i = 1; i <= n; i++)  valid_nums.push_back(i);

  solve_recursively(valid_nums);

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
