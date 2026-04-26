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
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  vector<int> freq(n+1);  //only care up until n
  for (int i = 0; i < n; i++) {
    if (a[i] <= n)  freq[a[i]]++;
  }
  int global_mex;
  for (global_mex = 0; global_mex <= n+1; global_mex++) {
    assert(global_mex <= n);
    if (freq[global_mex] == 0)  break;
  }

  PRINTVEC(freq);
  fprintf(stderr, "global mex: %d\n", global_mex);

  vector<long> dp(global_mex+1);
  dp[global_mex] = 0;
  for (int i = global_mex-1; i >= 0; i--) {
    long best = 1e18;
    for (int j = i+1; j <= global_mex; j++) {
      long candidate_score = dp[j] + ((long)freq[i]-1)*j + i;  //get mex to j, then pay j each time for each of freq[i] of i, except last one pays i
      best = min(best, candidate_score);
    }
    dp[i] = best;
  }

  PRINTVEC(dp);

  cout << dp[0] << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
