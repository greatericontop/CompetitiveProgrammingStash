#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d, ", _x); \
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
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    if (a[i] <= k)  b[i] = 1;
    else  b[i] = -1;
  }
  PRINTVEC(b);

  int first_left_i = -1;
  int second_left_i = -1;
  int prefix = 0;
  for (int i = 0; i < n; i++) {
    prefix += b[i];
    if (prefix >= 0) {
      first_left_i = i;
      break;
    }
  }
  for (int i = first_left_i+1; i < n; i++) {
    if (i == first_left_i+1 && prefix == 1) {
      // if last array ended with +1, then we can skip the first -1 (and we can't count it as a victory)
      if (b[i] == -1) {
        prefix--;
        continue;
      }
    }
    prefix += b[i];
    if (prefix >= 0) {
      second_left_i = i;
      break;
    }
  }

  int first_right_i = -1;
  int second_right_i = -1;
  prefix = 0;
  for (int i = n-1; i >= 0; i--) {
    prefix += b[i];
    if (prefix >= 0) {
      first_right_i = i;
      break;
    }
  }
  for (int i = first_right_i-1; i >= 0; i--) {
    if (i == first_right_i-1 && prefix == 1) {
      if (b[i] == -1) {
        prefix--;
        continue;
      }
    }
    prefix += b[i];
    if (prefix >= 0) {
      second_right_i = i;
      break;
    }
  }

  fprintf(stderr, "first_left_i = %d, second_left_i = %d\n", first_left_i, second_left_i);
  fprintf(stderr, "first_right_i = %d, second_right_i = %d\n", first_right_i, second_right_i);

  // win condition: leftleft or rightright or left,right
  if ((first_left_i != -1 && second_left_i != -1) || (first_right_i != -1 && second_right_i != -1)
      || (first_left_i != -1 && first_right_i != -1 && first_left_i + 1 < first_right_i)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
