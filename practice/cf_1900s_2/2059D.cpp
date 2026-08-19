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








constexpr int X = 1001;
constexpr long INF = LONG(1e18);
struct EdgeEntry {
  int to;
  int weight;
};

void solve() {
  int n, s1, s2;
  cin >> n >> s1 >> s2;
  AdjList adj1(n+1), adj2(n+1);
  int m1;  cin >> m1;
  FORI(m1) {
    int u, v;  cin >> u >> v;
    adj1[u].pb(v);
    adj1[v].pb(u);
  }
  int m2;  cin >> m2;
  FORI(m2) {
    int u, v;  cin >> u >> v;
    adj2[u].pb(v);
    adj2[v].pb(u);
  }

  vector<vector<EdgeEntry>> adj_big(X*n + 10);
  for (int a = 1; a <= n; a++) {
    for (int b = 1; b <= n; b++) {
      int node = a*X + b;
      for (int c : adj1[a]) {
        for (int d : adj2[b]) {
          int next_node = c*X + d;
          adj_big[node].pb({next_node, abs(c-d)});
        }
      }
    }
  }

  priority_queue<pairll, vector<pairll>, greater<pairll>> pq;
  vector<long> dist(X*n + 10, INF);
  vector<bool> visited(X*n + 10, false);
  dist[s1*X + s2] = 0;
  pq.push({0, s1*X + s2});
  while (!pq.empty()) {
    auto [d, node] = pq.top();  pq.pop();
    if (visited[node])  continue;  //maybe from previous its
    visited[node] = true;
    for (const auto e : adj_big[node]) {
      if (dist[e.to] > d + e.weight) {
        dist[e.to] = d + e.weight;
        pq.push({dist[e.to], e.to});  //m log m
      }
    }
  }

  vector<int> winners;
  for (int i = 1; i <= n; i++) {
    for (int j : adj1[i]) {
      // check if (i, j) is in adj2
      if (find(adj2[i].begin(), adj2[i].end(), j) != adj2[i].end()) {
        winners.pb(i);
        winners.pb(j);
        break;
      }
    }
  }

  long best = INF;
  for (int w : winners) {
    best = min(best, dist[w*X + w]);
  }
  cout << (best == INF ? -1 : best) << "\n";

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
