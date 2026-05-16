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









struct Entry {
    int low;
    int high;
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<bool>> grid(n, vector<bool>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int x; cin >> x;
      grid[i][j] = (x == 1);
    }
  }
  if ((n + m - 1) % 2 == 1) {
    cout << "NO\n";
    return;
  }
  int goal = (n + m - 1) / 2;

  vector<vector<Entry>> dp(n, vector<Entry>(m));
  dp[0][0] = {grid[0][0], grid[0][0]};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == 0 && j == 0)  continue;
      int low = INT_MAX, high = INT_MIN;
      if (i >= 1) {
        low = min(low, dp[i-1][j].low);
        high = max(high, dp[i-1][j].high);
      }
      if (j >= 1) {
        low = min(low, dp[i][j-1].low);
        high = max(high, dp[i][j-1].high);
      }
      assert(low < INT_MAX);
      assert(high > INT_MIN);
      low += grid[i][j];
      high += grid[i][j];
      dp[i][j] = {low, high};
    }
  }

  if (dp[n-1][m-1].low <= goal && goal <= dp[n-1][m-1].high) {
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
