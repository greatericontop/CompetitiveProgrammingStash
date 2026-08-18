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
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "1" : "0"); \
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
void subtree_size_inside_calc(int v, const AdjList& adj, const vector<bool>& insides, vector<int>& subtree_size_inside) {
  subtree_size_inside[v] = insides[v] ? 1 : 0;
  for (int child : adj[v]) {
    subtree_size_inside_calc(child, adj, insides, subtree_size_inside);
    subtree_size_inside[v] += subtree_size_inside[child];
  }
}










void solve() {
  int n;
  cin >> n;
  AdjList adj_undirected(n+1);
  FORI(n-1) {
    int u, v;  cin >> u >> v;
    adj_undirected[u].pb(v);
    adj_undirected[v].pb(u);
  }
  if (n == 2) {
    cout << "0\n";
    return;
  }
  int root = 1;
  while (root <= n && adj_undirected[root].size() == 1)  root++;
  assert(root <= n);
  fprintf(stderr, "root = %d\n", root);
  vector<int> parents(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(root, adj_undirected, parents, adj);
  vector<bool> leaves(n+1, false);
  vector<bool> adj_leaves(n+1, false);
  vector<bool> insides(n+1, false);
  for (int v = 1; v <= n; v++) {
    if (adj[v].empty()) {
      leaves[v] = true;
    }
  }
  for (int v = 1; v <= n; v++) {
    if (!leaves[v]) {
      for (int child : adj[v]) {
        if (leaves[child]) {
          adj_leaves[v] = true;
          break;
        }
      }
    }
  }
  for (int v = 1; v <= n; v++) {
    if (!leaves[v] && !adj_leaves[v]) {
      insides[v] = true;
    }
  }
  PRINTVECB(leaves);  PRINTVECB(adj_leaves);  PRINTVECB(insides);
  vector<int> subtree_size_inside(n+1, -1);
  subtree_size_inside_calc(root, adj, insides, subtree_size_inside);

  long ans = 0;
  for (int q = 1; q <= n; q++) {
    if (leaves[q])  continue;
    // Non-leaf q
    for (int child : adj[q]) {
      if (adj_leaves[child]) {
        ans += subtree_size_inside[child];
      }
    }
    if (q != root) {
      int par = parents[q];
      if (adj_leaves[par]) {
        ans += subtree_size_inside[root] - subtree_size_inside[q];  //subtree size inside of parent
      }
    }
  }
  long leafcount = 0;
  for (int v = 1; v <= n; v++)  {
    if (leaves[v])  leafcount++;
  }
  ans += leafcount * (n - leafcount);

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
