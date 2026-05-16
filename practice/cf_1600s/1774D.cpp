#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


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










void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> arrs(n, vector<int>(m));
  int count_1_total = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> arrs[i][j];
      if (arrs[i][j] == 1)  count_1_total++;
    }
  }
  if (count_1_total % n != 0) {
    cout << "-1\n";
    return;
  }
  int count_1_per_arr = count_1_total / n;
  vector<int> offsets(n);
  for (int i = 0; i < n; i++) {
    int count_1 = 0;
    for (int j = 0; j < m; j++) {
      if (arrs[i][j] == 1)  count_1++;
    }
    offsets[i] = count_1 - count_1_per_arr;
  }

  PRINTVEC(offsets);

  vector<vector<int>> ops;
  for (int j = 0; j < m; j++) {
    vector<int> rows_1_and_plus;
    vector<int> rows_0_and_minus;
    for (int i = 0; i < n; i++) {
      if (arrs[i][j] == 1 && offsets[i] > 0) {
        rows_1_and_plus.push_back(i);
      } else if (arrs[i][j] == 0 && offsets[i] < 0) {
        rows_0_and_minus.push_back(i);
      }
    }
    for (int i = 0; i < min(rows_1_and_plus.size(), rows_0_and_minus.size()); i++) {
      int row_1 = rows_1_and_plus[i];
      int row_0 = rows_0_and_minus[i];
      ops.push_back({row_1+1, row_0+1, j+1});
      offsets[row_1]--;
      offsets[row_0]++;
    }
  }

  for (int i = 0; i < n; i++)  assert(offsets[i] == 0);

  cout << ops.size() << "\n";
  for (const auto& op : ops) {
    cout << op[0] << " " << op[1] << " " << op[2] << "\n";
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
