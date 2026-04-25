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
  vector<int> A(n);
  for (int i = 0; i < n; i++)  cin >> A[i];

  // min cost starting at index i till end of array
  vector<int> dp(n+1, -1);

  // xor -> sorted list of indices with that xor
  vector<int> prefix_xor_array;
  map<int, vector<int>> prefixXors;
  map<int, int> dp_candidates;
  int prefixXor = 0;
  for (int i = 0; i < n; i++) {
    prefixXor ^= A[i];
    prefix_xor_array.push_back(prefixXor);
    prefixXors[prefixXor].push_back(i);
    dp_candidates[prefixXor] = INT_MAX;
  }

  dp[n] = 0;
  dp_candidates[prefix_xor_array[n-1]] = n-1;

  PRINTVEC(prefix_xor_array);

  for (int i = n-1; i >= 0; i--) {
    int targ = (i == 0) ? 0 : prefix_xor_array[i-1];
    if (A[i] == 0) {
      dp[i] = dp[i+1];
      dp_candidates[targ] = min(dp_candidates[targ], dp[i]+i-1);
      continue;
    }
    // find first index >= i (could be i itself) with prefix xor targ
    auto& indices = prefixXors[targ];
    auto it = lower_bound(indices.begin(), indices.end(), i);
    if (it == indices.end()) {
      dp[i] = 1 + dp[i+1]; // can't do any xor
    } else {
      dp[i] = dp_candidates[targ] - i;
    }
    dp_candidates[targ] = min(dp_candidates[targ], dp[i]+i-1);
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
