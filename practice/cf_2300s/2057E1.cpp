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
    return e1.weight > e2.weight;
  });

  AdjList adj_free(n+1);
  AdjList adj_cost(n+1);
  for (int p = m-1; p >= 0; p--) {
    // add edges to adj_free backwards so popping them off is easy
    adj_free[edges[p].a].pb(edges[p].b);
    adj_free[edges[p].b].pb(edges[p].a);
  }


  // dp[t][u][v] = distance from u to v
  int dp[m][n+1][n+1];

  for (int t = 0; t < m; t++) {
    // the highest weights up till index :t: cost
    // incrementally here we add edges[t]
    Edge e = edges[t];
    assert(adj_free[e.a].back() == e.b);  assert(adj_free[e.b].back() == e.a);
    adj_free[e.a].pop_back();  adj_free[e.b].pop_back();
    adj_cost[e.a].pb(e.b);  adj_cost[e.b].pb(e.a);

    // now run a bunch of BFSes
    for (int start = 1; start <= n; start++) {
      for (int v = 1; v <= n; v++)  dp[t][start][v] = INF;
      dp[t][start][start] = 0;
      vector<bool> visited(n+1, false);
      queue<int> bfs_queue, bfs_queue_priority;
      bfs_queue.push(start);
      // TODO: need visited
      // TODO: need queue and priority_queue
      while (!bfs_queue.empty() || !bfs_queue_priority.empty()) {
        int u;
        if (!bfs_queue_priority.empty()) {
          u = bfs_queue_priority.front();  bfs_queue_priority.pop();
        } else {
          u = bfs_queue.front();  bfs_queue.pop();
        }
        if (visited[u])  continue;  //so we don't visit it twice (if it was pushed in priority and normal)
        int u_dist = dp[t][start][u];
        for (int v : adj_free[u]) {
          if (dp[t][start][v] > u_dist) {
            dp[t][start][v] = u_dist;
            bfs_queue_priority.push(v);
          }
        }
        for (int v : adj_cost[u]) {
          if (dp[t][start][v] > u_dist + 1) {
            dp[t][start][v] = u_dist + 1;
            bfs_queue.push(v);
          }
        }
        visited[u] = true;
      }
    }
  }

  // Answer queries
  while (q --> 0) {
    int source, target, k;
    cin >> source >> target >> k;

    int l = 0, r = m-1;
    // dp[l] = low numbers, dp[r] = high numbers
    while (l < r) {
      int mid = l + (r-l)/2;
      if (dp[mid][source][target] < k) {
        // then we need to increase threshold (lower the bar) so that all paths clear
        l = mid+1;
      } else {
        r = mid;
      }
    }

    int ans = edges[l].weight;
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
