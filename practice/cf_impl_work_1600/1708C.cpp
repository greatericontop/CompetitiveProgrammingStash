#include <bits/stdc++.h>
using namespace std;
#define long long long


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










void solve() {
  int n;
  cin >> n;
  long q;
  cin >> q;
  vector<int> difficulty(n);
  for (int i = 0; i < n; i++)  cin >> difficulty[i];

  // Minimum IQ needed to choose all of i...end
  vector<int> dp(n+1);
  dp[n] = 0;
  for (int i = n-1; i >= 0; i--) {
    if (difficulty[i] <= dp[i+1]) {
      dp[i] = dp[i+1];
    } else {
      dp[i] = dp[i+1] + 1;
    }
  }

  string s;
  for (int i = 0; i < n; i++) {
    // Check if we can solo the rest
    if (dp[i] <= q) {
      for (int j = i; j < n; j++) {
        s += '1';
      }
      break;
    } else {
      if (difficulty[i] <= q)  s += '1';
      else  s += '0';
    }
  }

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
