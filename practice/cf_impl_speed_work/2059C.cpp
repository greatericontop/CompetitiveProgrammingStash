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













void solve() {
  int n;
  cin >> n;
  vector<vector<int>> queues(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> queues[i][j];
    }
  }
  vector<int> one_counts;
  for (int q = 0; q < n; q++) {
    int count = 0;
    for (int i = n-1; i >= 0; i--) {
      if (queues[q][i] == 1)  count++;
      else  break;
    }
    one_counts.push_back(count);
  }
  sort(one_counts.begin(), one_counts.end());

  int mex = 0;  //find >=mex to increase mex by 1
  int ptr = 0;  //points to first currently available elt
  while (ptr < n) {
    if (one_counts[ptr] >= mex) {
      mex++;
      ptr++;
    } else {
      ptr++;
    }
  }

  cout << mex << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
