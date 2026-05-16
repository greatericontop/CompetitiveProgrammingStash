#include <bits/stdc++.h>
using namespace std;


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
#define long long long
#define pb push_back
using pairii = pair<int, int>;
using pairll = pair<long, long>;










void solve() {
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  vector<bool> a(n*m);
  for (int i = 0; i < n*m; i++)  a[i] = (s[i] == '1');
  vector<int> prefix_a(n*m);
  prefix_a[0] = a[0];
  for (int i = 1; i < n*m; i++)  prefix_a[i] = prefix_a[i-1] + a[i];

  // columns
  vector<int> col_activations;
  for (int col = 0; col < m; col++) {
    for (int row = 0; row < n; row++) {
      if (a[row*m + col] == 1) {
        col_activations.push_back(row * m + col);
        break;
      }
    }
  }
  sort(col_activations.begin(), col_activations.end());
  PRINTVEC(col_activations);

  vector<int> row_answers(n*m);
  for (int i = 0; i < n*m; i++) {
    int ans = 0;
    int prev_i = i - m;
    if (prev_i >= 0) {
      ans += (prefix_a[i] - prefix_a[prev_i] >= 1) ? 1 : 0;
      ans += row_answers[prev_i];
    } else {
      ans += (prefix_a[i] >= 1) ? 1 : 0;
    }
    row_answers[i] = ans;
  }
  PRINTVEC(row_answers);


  int p = 0;
  for (int i = 0; i < n*m; i++) {
    while (p < col_activations.size() && col_activations[p] <= i) {
      p++;
    }
    cout << row_answers[i] + p << " ";
  }
  cout << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
