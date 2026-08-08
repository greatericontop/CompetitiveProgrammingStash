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








struct EdgeEntry {
  int to;
  long w;
};
constexpr long INF = LONG(5e18);


void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<EdgeEntry>> adj(n+1);
  FORI(m) {
    int u, v; long weight;
    cin >> u >> v >> weight;
    adj[u].pb({v, weight});
    adj[v].pb({u, weight});
  }

  vector<long> distances(n+1, INF);
  vector<bool> visited(n+1, false);
  priority_queue<pairll, vector<pairll>, greater<pairll>> frontier;
  distances[1] = 0;
  frontier.push({0, 1});  // {distance, vertex}
  while (!frontier.empty()) {
    auto [dist, u] = frontier.top();  frontier.pop();
    if (visited[u])  continue;
    visited[u] = true;
    for (auto e : adj[u]) {
      if (visited[e.to])  continue;
      // lazy version where i just push the new one which makes complexity a bit worse (n^2 log n^2)
      if (dist + e.w < distances[e.to]) {
        distances[e.to] = dist + e.w;
        frontier.push({distances[e.to], e.to});
      }
    }
  }

  if (distances[n] == INF) {
    cout << "inf\n";
    return;
  }
  if (distances[n] == 0) {
    cout << "0 0\n";
    return;
  }

  vector<long> dists_list;  dists_list.reserve(n);
  for (int i = 1; i <= n; i++) {
    // do not extend past
    if (distances[i] <= distances[n])  dists_list.pb(distances[i]);
  }
  sort(dists_list.begin(), dists_list.end());
  dists_list.erase(unique(dists_list.begin(), dists_list.end()), dists_list.end());
  assert(dists_list.front() == 0);
  assert(dists_list.back() == distances[n]);

  vector<string> answers_s;
  vector<long> answers_sz;
  for (int i = 0; i < INT(dists_list.size())-1; i++) {
    long sz_here = dists_list[i+1] - dists_list[i];
    // place 1 for all <dists_list[i+1] and 0 for all >=dist_list[i+1]
    string s(n, '.');
    for (int v = 1; v <= n; v++) {
      if (distances[v] < dists_list[i+1])  s[v-1] = '1';
      else  s[v-1] = '0';
    }
    assert(s[0] == '1' && s[n-1] == '0');
    answers_s.pb(s);
    answers_sz.pb(sz_here);
  }

  cout << dists_list.back() << " " << answers_s.size() << "\n";
  for (int i = 0; i < answers_s.size(); i++) {
    cout << answers_s[i] << " " << answers_sz[i] << "\n";
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
