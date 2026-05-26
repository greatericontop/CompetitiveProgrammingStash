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
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }
/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}

void twocolor(int v, const AdjList& adj, vector<bool>& twocoloring) {
  for (int child : adj[v]) {
    twocoloring[child] = !twocoloring[v];
    twocolor(child, adj, twocoloring);
  }
}










void solve() {
  int n;
  cin >> n;
  AdjList adj_u(n+1);
  FORI(n-1) {
    int u, v;
    cin >> u >> v;
    adj_u[u].pb(v);
    adj_u[v].pb(u);
  }
  int root = -1;
  for (int i = 1; i <= n; i++) {
    if (adj_u[i].size() == 2) {
      root = i;
      break;
    }
  }
  if (root == -1) {
    cout << "NO\n";
    return;
  }

  AdjList adj(n+1);
  vector<int> parents(n+1, -1);
  create_directed_adj(root, adj_u, parents, adj);

  int v1 = adj[root][0], v2 = adj[root][1];
  vector<bool> twocoloring(n+1);
  twocoloring[v1] = true;
  twocoloring[v2] = false;
  twocolor(v1, adj, twocoloring);
  twocolor(v2, adj, twocoloring);

  vector<pairii> edges; edges.reserve(n-1);
  for (int u = 1; u <= n; u++) {
    for (int v : adj[u]) {
      // twocoloring[root] is not defined
      if (twocoloring[v]) {
        edges.emplace_back(v, u);
      } else {
        edges.emplace_back(u, v);
      }
    }
  }

  cout << "YES\n";
  for (const auto& edge : edges) {
    cout << edge.first << " " << edge.second << "\n";
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
