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
/*
 * DSU
 * Code mostly copied from USACO Guide, with a few extra features added in
 */
class DSU {
private:
  vector<int> parents;
  vector<int> sizes;

public:
  int number_cc;
  int largest_cc;

  explicit DSU(int n) : parents(n), sizes(n, 1), number_cc(n), largest_cc(1) {
    for (int i = 0; i < n; i++)  parents[i] = i;
  }

  int find(int x) {
    return parents[x] == x ? x : (parents[x] = find(parents[x]));
  }

  bool unite(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);
    if (x_root == y_root)  return false;
    if (sizes[x_root] < sizes[y_root]) {
      swap(x_root, y_root);
    }
    sizes[x_root] += sizes[y_root];
    parents[y_root] = x_root;
    largest_cc = max(largest_cc, sizes[x_root]);
    number_cc--;
    return true;
  }

  bool connected(int x, int y) { return find(x) == find(y); }
};










struct Edge {
  int u;
  int v;
  int w;
};
struct TreeNode {
  int tag;
  int who;  //what vertex it corresponds to, or -1
  vector<int> adj;
};
struct DPEntry {
  int extra;
  long cost;
};


void propagate_tag(int v, vector<TreeNode>& tree) {
  for (int u : tree[v].adj) {
    tree[u].tag = min(tree[u].tag, tree[v].tag);
    propagate_tag(u, tree);
  }
}
void tree_dp(int v, vector<TreeNode>& tree, vector<DPEntry>& dp, const vector<int>& degree) {
  if (tree[v].adj.empty()) {
    assert(tree[v].who != -1);
    // Leaf node, so set extra to 1 if it's odd vertex, and 0 otherwise.
    dp[v].extra = (degree[tree[v].who] % 2 == 0) ? 0 : 1;
    dp[v].cost = 0;
  } else {
    assert(tree[v].who == -1);
    int extra = 0;  long cost = 0;
    for (int u : tree[v].adj) {
      tree_dp(u, tree, dp, degree);
      extra += dp[u].extra;
      cost += dp[u].cost;
    }
    int pairs = extra/2;
    dp[v].extra = extra - 2*pairs;
    // our tag is the best price you can pay
    dp[v].cost = cost + LONG(pairs)*LONG(tree[v].tag);
  }
}


void solve() {
  int n, m;
  cin >> n >> m;
  vector<Edge> edges(m);
  vector<int> degree(n+1);
  long edge_weight_sum = 0;
  FORI(m) {
    cin >> edges[i].u >> edges[i].v >> edges[i].w;
    degree[edges[i].u]++;
    degree[edges[i].v]++;
    edge_weight_sum += edges[i].w;
  }
  vector<TreeNode> tree;  tree.reserve(2*n + 100);
  tree.pb({});  //placeholder
  for (int v = 1; v <= n; v++) {
    tree.pb({.tag = INT_MAX, .who = v, .adj = {}});
  }
  vector<int> roots(n+1);
  FORI1(n)  roots[i] = i;  //dsu root x -> has its top node at tree[x]
  DSU dsu(n+1);

  for (const auto [u, v, w] : edges) {
    int u_dsu = dsu.find(u), v_dsu = dsu.find(v);
    if (u_dsu == v_dsu) {
      // just update tag
      int i = roots[u_dsu];
      tree[i].tag = min(tree[i].tag, w);
    } else {
      // merge
      int u_tree = roots[u_dsu], v_tree = roots[v_dsu];
      int new_tree_i = INT(tree.size());
      tree.pb({.tag = w, .who = -1, .adj = {u_tree, v_tree}});
      dsu.unite(u_dsu, v_dsu);
      int new_dsu = dsu.find(u_dsu);
      roots[new_dsu] = new_tree_i;
    }
  }
  assert(dsu.number_cc == 2);  //1 connected component, but also zero
  int root = roots[dsu.find(1)];  //root node of tree
  propagate_tag(root, tree);

  vector<DPEntry> dp(tree.size());
  tree_dp(root, tree, dp, degree);
  assert(dp[root].extra == 0);  //should have even number of odd-degree verts
  cout << edge_weight_sum + dp[root].cost << "\n";
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
