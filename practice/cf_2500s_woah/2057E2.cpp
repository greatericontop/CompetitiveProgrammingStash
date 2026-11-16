#include <bits/stdc++.h>
using namespace std;



#pragma GCC optimize("Ofast,unroll-loops")

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
    //largest_cc = max(largest_cc, sizes[x_root]);
    //number_cc--;
    return true;
  }

  bool connected(int x, int y) { return find(x) == find(y); }
};









struct Edge {
  int a;
  int b;
  int weight;
};




constexpr static int INF = 1e9;

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<Edge> edges(m);
  FORI(m) {
    cin >> edges[i].a >> edges[i].b >> edges[i].weight;
  }
  sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
  });

  AdjList adj_free(n+1);
  AdjList adj_cost(n+1);
  for (int p = m-1; p >= 0; p--) {
    // add edges to adj_free backwards so popping them off is easy
    adj_cost[edges[p].a].pb(edges[p].b);
    adj_cost[edges[p].b].pb(edges[p].a);
  }


  // dp[t][u][v] = distance from u to v
  int dp[n][n+1][n+1];
  int what_value[n];
  int tmax = 0;
  DSU dsu(n+1);

  int apsp[n+1][n+1];
  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      apsp[u][v] = INF;
    }
  }
  for (int v = 1; v <= n; v++)  apsp[v][v] = 0;
  for (int u = 1; u <= n; u++) {
    for (int v : adj_cost[u]) {
      apsp[u][v] = min(apsp[u][v], 1);
    }
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        apsp[i][j] = min(apsp[i][j], apsp[i][k] + apsp[k][j]);
      }
    }
  }


  for (int tt = 0; tt < m; tt++) {
    // free up the *cheapest* one
    Edge e = edges[tt];
    assert(adj_cost[e.a].back() == e.b);  assert(adj_cost[e.b].back() == e.a);
    adj_cost[e.a].pop_back();  adj_cost[e.b].pop_back();
    adj_free[e.a].pb(e.b);  adj_free[e.b].pb(e.a);

    if (dsu.connected(e.a, e.b)) {
      // do nothing
    } else {
      dsu.unite(e.a, e.b);
      what_value[tmax] = e.weight;

      int t = tmax;

      // update apsp[a][b] to 0
      apsp[e.a][e.b] = 0;
      for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
          apsp[u][v] = min(apsp[u][v], apsp[u][e.a] + apsp[e.b][v]);
        }
      }
      apsp[e.b][e.a] = 0;
      for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
          apsp[u][v] = min(apsp[u][v], apsp[u][e.b] + apsp[e.a][v]);
        }
      }

      memcpy(dp[t], apsp, sizeof(apsp));

      tmax++;
    }
  }
  assert(tmax <= n);

  // Answer queries
  while (q --> 0) {
    int source, target, k;
    cin >> source >> target >> k;

    int l = 0, r = tmax-1;
    while (l < r) {
      int mid = l + (r-l)/2;
      if (dp[mid][source][target] < k) {
        // good, then try going down (lower t = more expensive)
        r = mid;
      } else {
        l = mid+1;
      }
    }

    int ans = what_value[l];
    cout << ans << " ";
  }
  cout << "\n";

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
