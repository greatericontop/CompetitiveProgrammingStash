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










struct Op {
  int a, b, c;
};
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

void solve() {
  int n, m;
  cin >> n >> m;
  vector<set<int>> adj(n+1);
  FORI(m) {
    int u, v;  cin >> u >> v;
    adj[u].insert(v);
    adj[v].insert(u);
  }
  auto printgraph = [&]() {
    for (int v = 1; v <= n; v++) {
      fprintf(stderr, "%d:  ", v);
      for (int u : adj[v])  fprintf(stderr, "%d ", u);
      fprintf(stderr, "\n");
    }
  };

  vector<Op> ops;
  auto do_op = [&](int a, int b, int c) {
    ops.pb(Op{a, b, c});
    if (adj[a].count(b)) {
      adj[a].erase(b);
      adj[b].erase(a);
    } else {
      adj[a].insert(b);
      adj[b].insert(a);
    }
    if (adj[a].count(c)) {
      adj[a].erase(c);
      adj[c].erase(a);
    } else {
      adj[a].insert(c);
      adj[c].insert(a);
    }
    if (adj[b].count(c)) {
      adj[b].erase(c);
      adj[c].erase(b);
    } else {
      adj[b].insert(c);
      adj[c].insert(b);
    }
  };
  set<int> non_deg1_verts;
  auto check_vert = [&](int v) {
    if (adj[v].size() > 1) {
      non_deg1_verts.insert(v);
    } else {
      non_deg1_verts.erase(v);
    }
  };

  for (int v = 1; v <= n; v++)  check_vert(v);
  while (!non_deg1_verts.empty()) {
    int v = *non_deg1_verts.begin();
    assert(adj[v].size() >= 2);
    auto it = adj[v].begin(), it2 = next(it);
    int b = *it, c = *it2;
    do_op(v, b, c);
    check_vert(v);
    check_vert(b);
    check_vert(c);
    printgraph();
  }
  assert(ops.size() <= m);
  for (int i = 1; i <= n; i++)  assert(adj[i].size() <= 1);

  DSU dsu(n+1);
  for (int v = 1; v <= n; v++) {
    for (int u : adj[v]) {
      dsu.unite(u, v);
    }
  }
  int root = -1;
  for (int r = 1; r <= n; r++) {
    if (adj[r].size() >= 1) {
      root = r;
      break;
    }
  }
  if (root == -1) {
    // Do nothing, graph is empty
    for (int i = 1; i <= n; i++)  assert(adj[i].empty());
  } else {
    // Tree building
    root = dsu.find(root);
    for (int v = 1; v <= n; v++) {
      if (dsu.connected(v, root))  continue;
      int rootadj = *adj[root].begin();
      do_op(root, v, rootadj);
      dsu.unite(v, root);
      root = dsu.find(root);
    }
  }

  cout << ops.size() << "\n";
  for (const auto& op : ops) {
    cout << op.a << " " << op.b << " " << op.c << "\n";
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
