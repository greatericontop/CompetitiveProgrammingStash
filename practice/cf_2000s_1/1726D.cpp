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










struct Edge {
  int u, v;
};
struct AdjEntry {
  int to;
  int idx;
};

void dfs(int v, vector<bool>& visited, set<int>& non_tree_edges, const vector<vector<AdjEntry>>& adj) {
  assert(!visited[v]);  visited[v] = true;
  for (const auto& entry : adj[v]) {
    int u = entry.to;
    if (!visited[u]) {
      non_tree_edges.erase(entry.idx);
      dfs(u, visited, non_tree_edges, adj);
    }
  }
}
/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, vector<vector<AdjEntry>>& adj_undirected, vector<int>& parents, vector<vector<AdjEntry>>& adj) {
  for (auto [child, idx] : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].pb({child, idx});
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}

inline bool cmpabcd(int a, int b, pairii cd) {
  return (a == cd.first && b == cd.second) || (a == cd.second && b == cd.first);
}


void solve() {
  int n, m;  cin >> n >> m;
  vector<vector<AdjEntry>> adj_undirected(n+1);
  vector<Edge> edges(m);
  FORI(m) {
    int u, v;  cin >> u >> v;
    edges[i] = {u, v};
    adj_undirected[u].push_back({v, i});
    adj_undirected[v].push_back({u, i});
  }

  // Find indices of non-tree edges
  set<int> non_tree_edges;
  FORI(m)  non_tree_edges.insert(i);
  vector<bool> visited(n+1, false);
  dfs(1, visited, non_tree_edges, adj_undirected);

  bool is_easy = true;
  if (non_tree_edges.size() == 3) {
    set<int> verts;
    for (int idx : non_tree_edges) {
      verts.insert(edges[idx].u);
      verts.insert(edges[idx].v);
    }
    if (verts.size() == 3) {
      is_easy = false;
      //
      // Solve for verts size 3 case
      //
      int a = *verts.begin(), b = *next(verts.begin()), c = *next(next(verts.begin()));  // root at a
      fprintf(stderr, "a=%d, b=%d, c=%d\n", a, b, c);
      vector<vector<AdjEntry>> adj_undirected2(n+1);  //with the two problematic edges removed
      for (int i = 0; i < m; i++) {
        if (non_tree_edges.count(i))  continue;
        int u = edges[i].u, v = edges[i].v;
        adj_undirected2[u].push_back({v, i});
        adj_undirected2[v].push_back({u, i});
      }
      vector<int> parents(n+1, -1);
      vector<vector<AdjEntry>> adj(n+1);
      create_directed_adj(a, adj_undirected2, parents, adj);

      // all will be 0, except in 1 we will have b->parent, c->parent, a->b, and a->c
      pairii bb = {b, parents[b]}, cc = {c, parents[c]};
      string ans(m, '0');
      for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (cmpabcd(u, v, bb) || cmpabcd(u, v, cc))  ans[i] = '1';
        if (cmpabcd(u, v, {a, b}) || cmpabcd(u, v, {a, c}))  ans[i] = '1';
      }
      cout << ans << "\n";
      return;
    }
  }
  if (is_easy) {
    fprintf(stderr, "easy case\n");
    // Otherwise, just color these edges differently
    string ans(m, '0');
    for (int idx : non_tree_edges)  ans[idx] = '1';
    cout << ans << "\n";
    return;
  }
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
