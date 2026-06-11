#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECL(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:   ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECP(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%d %d],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECPL(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%lld %lld],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









int subset_sum(const vector<int>& nums, int n) {
  int goal = n/2;
  vector<bool> dp(goal+1, false);
  dp[0] = true;
  for (int num : nums) {
    // reverse order to enforce one use only
    for (int i = goal-num; i >= 0; i--) {
      if (dp[i])  dp[i+num] = true;
    }
  }
  for (int i = goal; i >= 0; i--) {
    if (dp[i])  return i;
  }
  assert(false);
}


void calc_subtree_size(int v, vector<int>& subtree_size, const AdjList& adj) {
  subtree_size[v] = 1;
  for (int u : adj[v]) {
    calc_subtree_size(u, subtree_size, adj);
    subtree_size[v] += subtree_size[u];
  }
}


void calc_dp(int v, vector<long>& dp, const AdjList& adj, const vector<int>& subtree_size) {
  if (adj[v].empty()) {
    dp[v] = 0;
    return;
  }

  vector<int> nums;  nums.reserve(adj[v].size());
  long dp_sum = 0;
  for (int u : adj[v]) {
    calc_dp(u, dp, adj, subtree_size);
    nums.pb(subtree_size[u]);
    dp_sum += dp[u];
  }
  int best_split = subset_sum(nums, subtree_size[v]);
  dp_sum += LONG(best_split) * LONG(subtree_size[v]-1 - best_split);
  dp[v] = dp_sum;
}



void solve() {
  int n;
  cin >> n;
  AdjList adj(n+1);
  for (int v = 2; v <= n; v++) {
    int p;
    cin >> p;
    adj[p].pb(v);
  }
  vector<int> subtree_size(n+1, 0);
  calc_subtree_size(1, subtree_size, adj);
  vector<long> dp(n+1, -1);
  calc_dp(1, dp, adj, subtree_size);

  cout << dp[1] << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
