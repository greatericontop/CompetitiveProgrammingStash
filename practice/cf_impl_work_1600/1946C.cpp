#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d %d, ", _x.first, _x.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif









using AdjList = vector<vector<int>>;
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}


void dp_recursively(int v, AdjList& adj, vector<pair<int, int>>& dp, int x) {
  int total_ccs = 0;
  int total_extra = 0;
  for (int child : adj[v]) {
    dp_recursively(child, adj, dp, x);
    total_ccs += dp[child].first;
    total_extra += dp[child].second;
  }
  total_extra++;  //ourselves
  if (total_extra >= x) {
    dp[v] = {total_ccs+1, 0};
  } else {
    dp[v] = {total_ccs, total_extra};
  }
}


void solve() {
  int n, req_ccs;
  cin >> n >> req_ccs;
  req_ccs++;  //k connected components required
  AdjList adj_undirected(n);
  for (int i = 0; i < n-1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    adj_undirected[u].push_back(v);
    adj_undirected[v].push_back(u);
  }
  vector<int> parents(n);
  AdjList adj(n);
  create_directed_adj(0, adj_undirected, parents, adj);


  int low = 0, high = n;
  while (low < high) {
    // How many CCs of size at least x can we get?
    int x = low + (high-low+1)/2;
    vector<pair<int, int>> dp(n);
    dp_recursively(0, adj, dp, x);
    fprintf(stderr, "x = %d\n", x);
    PRINTVEC(dp);
    if (dp[0].first >= req_ccs) {  //is it a valid sol
      low = x;
    } else {
      high = x-1;
    }
  }

  cout << low << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
