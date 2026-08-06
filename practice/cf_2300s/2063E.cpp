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







void dfs_size_and_depth(int v, const AdjList& adj, vector<int>& subtree_size, vector<int>& depth) {
  subtree_size[v] = 1;
  for (int child : adj[v]) {
    depth[child] = depth[v] + 1;
    dfs_size_and_depth(child, adj, subtree_size, depth);
    subtree_size[v] += subtree_size[child];
  }
}

void lca_depth_summer(int v, const AdjList& adj, const vector<int>& depth, const vector<int>& subtree_size, long& lca_depth_sum_all_pairs) {
  long total_children = 0;
  for (int child : adj[v]) {
    total_children += subtree_size[child];
    lca_depth_summer(child, adj, depth, subtree_size, lca_depth_sum_all_pairs);
  }
  long x = 0;
  for (int child : adj[v]) {
    x += subtree_size[child] * (total_children - subtree_size[child]);
  }
  assert(x % 2 == 0);
  x /= 2;
  // also add self + any child (do not divide this by 2)
  x += total_children;
  lca_depth_sum_all_pairs += depth[v] * x;
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
  vector<int> _parents(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(1, adj_undirected, _parents, adj);

  vector<int> subtree_size(n+1, -1);
  vector<int> depth(n+1, -1);
  depth[1] = 0;
  dfs_size_and_depth(1, adj, subtree_size, depth);

  // Calculate sum of (depth) for each node above us
  // Sort in order of depth
  vector<pairii> depth_and_node(n);
  FORI1(n) {
    depth_and_node[i-1] = {depth[i], i};
  }
  sort(depth_and_node.begin(), depth_and_node.end());
  long sum_depth_all_pairs = 0;
  long accumulated = 0;
  for (auto [_d, v] : depth_and_node) {
    sum_depth_all_pairs += accumulated;
    accumulated += depth[v];
    assert(sum_depth_all_pairs <= LONG(1e18));
    fprintf(stderr, "  vertex %d, sum_depth_all_pairs = %ld\n", v, sum_depth_all_pairs);
  }

  // Sum of LCA depth
  long lca_depth_sum_all_pairs = 0;
  lca_depth_summer(1, adj, depth, subtree_size, lca_depth_sum_all_pairs);

  // Compensate for ancestor pairs
  long compensate_for_ancestors = 0;
  for (int v = 1; v <= n; v++) {
    compensate_for_ancestors += depth[v];
  }

  // Ans = sum(2*shortest path to lca - 1) + compensate_for_ancestors
  //   because ancestor ones will be counted as -1 instead of 0
  // = 2*(shortestpathtolca) - number pairs + compensate for ancestors
  //     (sum_depth_all_pairs-lca_depth_sum_all_pairs)
  fprintf(stderr, "sum_depth_all_pairs = %ld, lca_depth_sum_all_pairs = %ld, compensate_for_ancestors = %ld\n", sum_depth_all_pairs, lca_depth_sum_all_pairs, compensate_for_ancestors);
  long ans = 2*(sum_depth_all_pairs-lca_depth_sum_all_pairs) - LONG(n)*LONG(n-1)/2 + compensate_for_ancestors;
  cout << ans << "\n";
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
