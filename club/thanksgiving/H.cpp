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




struct Edge {
  int u;
  int v;
  int id;
  bool tree;
};
struct EdgeEntry {
  int v;
  int id;
};

void create_directed_adj(int v, vector<Edge>& edges, vector<vector<EdgeEntry>>& adj_undirected, vector<int>& parents, vector<vector<EdgeEntry>>& adj, vector<bool>& visited) {
  for (auto [child, eid] : adj_undirected[v]) {
    if (child == parents[v])  continue;
    if (visited[child])  continue;  //don't recurse
    visited[child] = true;
    parents[child] = v;
    adj[v].push_back({child, eid});
    edges[eid].tree = true;
    create_directed_adj(child, edges, adj_undirected, parents, adj, visited);
  }
}







void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<EdgeEntry>> adj_whole(n+1);
  vector<Edge> edges(m);
  FORI(m) {
    int u, v;  cin >> u >> v;
    edges[i] = {u, v, i, false};
    adj_whole[u].push_back({v, i});
    adj_whole[v].push_back({u, i});
  }
  vector<vector<EdgeEntry>> adj_tree(n+1);
  vector<int> parents(n+1);
  vector<bool> visited(n+1);  visited[1] = true;
  create_directed_adj(1, edges, adj_whole, parents, adj_tree, visited);


  vector<Edge> remaining_edges;
  for (Edge e : edges) {
    if (!e.tree)  remaining_edges.push_back(e);
  }

  // u is above v
  auto swap_higher = [&](int& u, int& v) {
    int v1 = v;
    while (v1 != 0) {
      v1 = parents[v1];
      if (v1 == u) {
        return;
      }
    }

    int u1 = u;
    while (u1 != 0) {
      u1 = parents[u1];
      if (u1 == v) {
        break;
      }
    }
    assert(u1 != 0);

    // else
    swap(u, v);
  };

  if (remaining_edges.size() == 3) {
    set<int> verts;
    for (Edge e : remaining_edges) {
      verts.insert(e.v);
      verts.insert(e.u);
    }
    if (verts.size() == 3) {
      // need to replace one
      Edge replacement = remaining_edges[0];
      edges[replacement.id].tree = true;
      int u = replacement.u, v = replacement.v;
      fprintf(stderr, "choosing to convert edge %d %d (id %d)\n", u, v, replacement.id);
      // Check which vertex is higher
      swap_higher(u, v);
      // remove edge from v to parent[v]
      for (EdgeEntry e : adj_tree[parents[v]]) {
        if (e.v == v) {
          assert(edges[e.id].tree);
          fprintf(stderr, "nontree id=%d (%d)\n", e.id, e.v);
          edges[e.id].tree = false;
          goto good;
        }
      }
      assert(false);
      good:
      ;
    }
  }

  string ans(m, '.');
  for (int i = 0; i < m; i++) {
    ans[i] = (edges[i].tree) ? '1' : '0';
  }
  cout << ans << endl;


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
