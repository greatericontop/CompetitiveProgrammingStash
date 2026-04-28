#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d %d, ", _x.first, _x.second); \
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
  vector<pair<int, int>> A(n);
  bool exists_1 = false, exists_0 = false;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int count_0 = 0, count_1 = 0;
    for (char c : s) {
      if (c == '0') {
        count_0++;
        exists_0 = true;
      } else {
        count_1++;
        exists_1 = true;
      }
    }
    A[i] = {count_0, count_1};
  }
  if (!exists_0 || !exists_1) {
    cout << "0\n";
    return;
  }

  int total_moves = 0;
  int minimum_difference = INT_MAX;
  bool moved_0 = false, moved_1 = false;

  for (const auto& [count_0, count_1] : A) {
    if (count_0 < count_1) {
      total_moves += count_0;
      minimum_difference = min(minimum_difference, count_1 - count_0);
      moved_0 = true;
    } else if (count_0 > count_1) {
      total_moves += count_1;
      minimum_difference = min(minimum_difference, count_0 - count_1);
      moved_1 = true;
    } else {
      total_moves += count_0;
      minimum_difference = 0;
    }
  }

  if ((!moved_0) || (!moved_1)) {
    fprintf(stderr, "add minimum_difference: %d\n", minimum_difference);
    total_moves += minimum_difference;
  }

  cout << total_moves << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
