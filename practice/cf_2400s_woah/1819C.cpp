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


/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}
void subtree_size_dp(int v, AdjList& adj, vector<int>& subtree_size) {
  subtree_size[v] = 1;
  for (int child : adj[v]) {
    subtree_size_dp(child, adj, subtree_size);
    subtree_size[v] += subtree_size[child];
  }
}


bool traverse_backward(int cur, AdjList& adj, vector<int>& subtree_size, vector<int>& cur_path);
/*
 * Rec spec: visit :cur: first (adding it to :cur_path:), and end with visiting a node that is a child of :cur:
 * Or only :cur: if it is a leaf
 * Return true/false if successful
 */
bool traverse_forward(int cur, AdjList& adj, vector<int>& subtree_size, vector<int>& cur_path) {
  if (adj[cur].empty()) {
    cur_path.pb(cur);
    return true;
  }
  vector<int> trivial_children;
  int nontrivial_child = -1;
  for (int child : adj[cur]) {
    if (subtree_size[child] == 1) {
      trivial_children.pb(child);
    } else {
      if (nontrivial_child != -1)  return false;  // only one
      nontrivial_child = child;
    }
  }

  cur_path.pb(cur);
  if (nontrivial_child != -1) {
    bool ret = traverse_backward(nontrivial_child, adj, subtree_size, cur_path);
    if (!ret)  return false;
  }
  for (int child : trivial_children) {
    cur_path.pb(child);
  }
  return true;
}


/*
 * Visit a child of :cur: first and then visit :cur: at the end
 */
bool traverse_backward(int cur, AdjList& adj, vector<int>& subtree_size, vector<int>& cur_path) {
  if (adj[cur].empty()) {
    cur_path.pb(cur);
    return true;
  }
  vector<int> trivial_children;
  int nontrivial_child = -1;
  for (int child : adj[cur]) {
    if (subtree_size[child] == 1) {
      trivial_children.pb(child);
    } else {
      if (nontrivial_child != -1)  return false;  // only one
      nontrivial_child = child;
    }
  }

  for (int child : trivial_children) {
    cur_path.pb(child);
  }
  if (nontrivial_child != -1) {
    bool ret = traverse_forward(nontrivial_child, adj, subtree_size, cur_path);
    if (!ret)  return false;
  }
  cur_path.pb(cur);
  return true;
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

  vector<int> subtree_size(n+1, 0);
  subtree_size_dp(1, adj, subtree_size);

  vector<int> path;
  bool ret = traverse_forward(1, adj, subtree_size, path);
  if (!ret) {
    cout << "No\n";
  } else {
    cout << "Yes\n";
    for (int v : path) {
      cout << v << " ";
    }
    cout << "\n";
  }


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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
