#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


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
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "true" : "false"); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
  #define PRINTVECB(...)
#endif
#define long int64_t
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
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;
/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}



constexpr int IMPOSSIBLE = -INT(1e9);
void dp_dfs(int v, const AdjList& adj, vector<int>& dp, const vector<int>& chip_verts_counts) {
  for (int child : adj[v]) {
    dp_dfs(child, adj, dp, chip_verts_counts);
    if (dp[child] == IMPOSSIBLE) {
      dp[v] = IMPOSSIBLE;
      return;
    }
  }

  // negative = requested, positive = space available
  int request_count = 0;
  int highest_requested = 0;
  int highest_available = 0;
  if (chip_verts_counts[v] > 0) {
    request_count++;
    highest_requested = chip_verts_counts[v];
  }
  for (int u : adj[v]) {
    if (dp[u] < 0) {
      request_count++;
      highest_requested = max(highest_requested, -dp[u]);
    } else {
      highest_available = max(highest_available, dp[u]);
    }
  }

  if (request_count >= 2) {
    dp[v] = IMPOSSIBLE;
  } else if (request_count == 1) {
    if (highest_available + 1 >= highest_requested) {
      // highest_available + ourselves is the longest requested path we can accumulate
      // then we can stay inside ourselves and be neutral
      dp[v] = 0;
    } else {
      // requested more from above
      int requested_amount = highest_requested - 1;
      dp[v] = -requested_amount;
    }
  } else {
    // no requests, then propagate up the highest available, including ourselves (if none available, then it's just 1)
    dp[v] = highest_available + 1;
  }
}


bool is_possible(int n, int k, int turns, const AdjList& adj, const vector<int>& chip_locs) {
  vector<int> chip_verts_counts(n+1, -2);
  for (int i = 0; i < k; i++) {
    int chip = chip_locs[i];
    chip_verts_counts[chip] = (turns / k) + (i < (turns % k) ? 1 : 0) + 1;
    // chip_verts_counts[v] = path length required (including self)
  }
  fprintf(stderr, "  called for turns %d\n  ", turns);
  PRINTVEC(chip_verts_counts);

  vector<int> dp(n+1, -676767677);
  dp_dfs(1, adj, dp, chip_verts_counts);
  fprintf(stderr, "  ");  PRINTVEC(dp);
  return dp[1] >= 0;
}









void solve() {
  int n;
  cin >> n;
  AdjList adj_undirected(n+1);
  FORI(n-1) {
    int u, v;
    cin >> u >> v;
    adj_undirected[u].pb(v);
    adj_undirected[v].pb(u);
  }
  AdjList adj(n+1);
  vector<int> parents(n+1, -1);
  create_directed_adj(1, adj_undirected, parents, adj);
  int k;
  cin >> k;
  vector<int> chip_locs(k);
  FORI(k) {
    cin >> chip_locs[i];
  }

  int l = 0, r = n;
  while (l < r) {
    int mid = l + (r-l+1)/2;
    if (is_possible(n, k, mid, adj, chip_locs)) {
      fprintf(stderr, "turns %d is possible\n", mid);
      l = mid;
    } else {
      fprintf(stderr, "turns %d is not possible\n", mid);
      r = mid - 1;
    }
  }

  cout << l << "\n";


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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
