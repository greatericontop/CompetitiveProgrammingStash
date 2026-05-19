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
using AdjList = vector<set<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }


/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj, vector<int>& heights, int curheight) {
  heights[v] = curheight;
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].insert(child);
    create_directed_adj(child, adj_undirected, parents, adj, heights, curheight+1);
  }
}









void solve() {
  int n;
  cin >> n;
  AdjList adj_u(n+1);
  FORI(n-1) {
    int u, v;
    cin >> u >> v;
    adj_u[u].insert(v);
    adj_u[v].insert(u);
  }
  vector<int> parents(n+1, -1);
  vector<int> heights(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(1, adj_u, parents, adj, heights, 0);

  vector<int> verts_per_height(n+1, 0);
  vector<vector<int>> actual_verts_per_height(n+1);
  for (int v = 1; v <= n; v++) {
    verts_per_height[heights[v]]++;
    actual_verts_per_height[heights[v]].pb(v);
  }
  // suffix_sum[h]: how many verts >= height h
  vector<int> suffix_sum(n+2);
  suffix_sum[n+1] = 0;
  for (int h = n; h >= 0; h--)  suffix_sum[h] = suffix_sum[h+1] + verts_per_height[h];


  int best = INT_MAX;
  int deletions_above = 0;
  // All leaves will be height h
  for (int h = 1; h <= n; h++) {
    int num_verts_greater = suffix_sum[h+1];
    fprintf(stderr, "at height %d, deletions above = %d, num verts greater = %d\n", h, deletions_above, num_verts_greater);
    best = min(best, deletions_above + num_verts_greater);

    // Now delete all leaves at height h in preparation for the next one
    for (int v : actual_verts_per_height[h]) {
      int v1 = v;
      while (v1 != 1 && adj[v1].empty()) {
        int p = parents[v1];
        adj[p].erase(v1);
        v1 = p;
        deletions_above++;
      }
    }
  }

  cout << best << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
