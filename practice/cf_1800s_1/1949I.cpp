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
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
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
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









void twocolor(int v, const vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& twocoloring, int counts[2]) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (visited[u])  continue;
    twocoloring[u] = !twocoloring[v];
    counts[twocoloring[u]]++;
    twocolor(u, adj, visited, twocoloring, counts);
  }
}

bool check_bipartite(int v, const vector<vector<int>>& adj, vector<bool>& visited2, vector<bool>& twocoloring) {
  visited2[v] = true;
  for (int u : adj[v]) {
    if (twocoloring[u] == twocoloring[v])  return false;  //check entire adj even if visited
    if (visited2[u])  continue;
    if (!check_bipartite(u, adj, visited2, twocoloring))  return false;
  }
  return true;
}


void solve() {
  int n;
  cin >> n;
  vector<int> x(n), y(n), r(n);
  FORI(n) {
    cin >> x[i] >> y[i] >> r[i];
  }

  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      long dx = x[i] - x[j], dy = y[i] - y[j];
      long rr = r[i] + r[j];
      if (dx*dx + dy*dy == rr*rr) {
        adj[i].pb(j);
        adj[j].pb(i);
      }
    }
  }

  vector<bool> visited(n, false);
  vector<bool> visited2(n, false);
  vector<bool> twocoloring(n, false);

  for (int i = 0; i < n; i++) {
    if (visited[i])  continue;
    int counts[2] = {1, 0};  //false at i
    twocolor(i, adj, visited, twocoloring, counts);
    if (check_bipartite(i, adj, visited2, twocoloring)) {
      if (counts[0] != counts[1]) {
        cout << "YES\n";
        return;
      }
    }
  }

  // No bipartite & unbalanceable CCs
  cout << "NO\n";

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
