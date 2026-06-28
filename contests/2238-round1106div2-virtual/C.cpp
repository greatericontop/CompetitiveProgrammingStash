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









void dfs_longest_depth(int v, AdjList& adj, vector<pairii>& longest_depth) {
  if (adj[v].empty()) {
    longest_depth[v] = {0, 0};
    return;
  }
  int best = 0, second_best = 0;
  for (int u : adj[v]) {
    dfs_longest_depth(u, adj, longest_depth);
    int depth = longest_depth[u].first + 1;
    if (depth >= best) {
      second_best = best;
      best = depth;
    } else if (depth > second_best) {
      second_best = depth;
    }
  }
  longest_depth[v] = {best, second_best};
}


void dfs_dp(int v, AdjList& adj, vector<pairii>& longest_depth, vector<long>& dp) {
  if (adj[v].empty()) {
    dp[v] = 1;
    return;
  }

  long total = 0;

  for (int u : adj[v]) {
    dfs_dp(u, adj, longest_depth, dp);
    total += dp[u];
  }

  total += longest_depth[v].second + 1;

  dp[v] = total;
}


void solve() {
  int n;
  cin >> n;
  AdjList adj(n+1);
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p;
    adj[p].pb(i);
  }

  vector<pairii> longest_depth(n+1);
  dfs_longest_depth(1, adj, longest_depth);

  vector<long> dp(n+1);
  dfs_dp(1, adj, longest_depth, dp);

  cout << dp[1] << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
