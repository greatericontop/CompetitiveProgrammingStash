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











void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}

void calcdepth(int v, AdjList& adj, vector<int>& depth) {
  for (int child : adj[v]) {
    depth[child] = depth[v] + 1;
    calcdepth(child, adj, depth);
  }
}


void solve() {
  int n, a, b;
  cin >> n >> a >> b;
  a--; b--;
  fprintf(stderr, "n=%d a=%d b=%d\n", n, a, b);
  AdjList adj_orig(n);
  FORI(n - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj_orig[u].pb(v);
    adj_orig[v].pb(u);
  }
  AdjList adj1(n);
  vector<int> parents1(n);
  parents1[b] = b;
  create_directed_adj(b, adj_orig, parents1, adj1);
  PRINTVEC(parents1);
  vector<int> vertices_from_a_to_b;
  int v = a;
  while (v != b) {
    vertices_from_a_to_b.pb(v);
    //fprintf(stderr, "%d -> %d\n", v, parents1[v]);
    v = parents1[v];
  }
  vertices_from_a_to_b.pb(b);
  PRINTVEC(vertices_from_a_to_b);

  int ct = vertices_from_a_to_b.size()-1;
  int new_root, travel_penalty;
  if (ct % 2 == 0) {
    new_root = vertices_from_a_to_b[ct/2];
    travel_penalty = ct/2;
  } else {
    new_root = vertices_from_a_to_b[ct/2];
    travel_penalty = ct/2 + 1;
  }


  AdjList adj2(n);
  vector<int> parents2(n);
  parents2[new_root] = new_root;
  create_directed_adj(new_root, adj_orig, parents2, adj2);
  vector<int> depth(n);
  depth[new_root] = 0;
  calcdepth(new_root, adj2, depth);
  int maxdepth = accumulate(depth.begin(), depth.end(), -1000, [](int a, int b) { return max(a, b); });
  int traversal_time = 2*(n-1) - maxdepth;
  cout << traversal_time + travel_penalty << "\n";





}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
