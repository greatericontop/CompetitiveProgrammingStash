#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


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
  int onect = 0;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      if (a[i][j] == 1)  onect++;
    }
  }

  int goal = onect/2;
  long ans = ((long)goal) * (long)(onect - goal);

  int i = n-1;
  int j = 0;
  for (; i >= 0; i--) {
    if (goal == 0)  break;
    for (j = 0; j < m; j++) {
      if (a[i][j] == 1)  goal--;
      if (goal == 0)  break;
    }
    if (goal == 0)  break;
  }
  assert(i >= 0);
  // (i, j) included in the bottom cut

  string s;
  for (int k = 0; k < i; k++)  s += 'D';
  for (int k = 0; k <= j; k++)  s += 'R';
  s += 'D';
  for (int k = j+1; k < m; k++)  s += 'R';
  for (int k = i+1; k < n; k++)  s += 'D';

  cout << ans << "\n";
  cout << s << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
