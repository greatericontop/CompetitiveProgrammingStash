#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d, ", _x); \
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

void count_layers(int v, AdjList& adj, vector<int>& counts, int cur_layer) {
  counts[cur_layer]++;  //from v
  for (int child : adj[v]) {
    count_layers(child, adj, counts, cur_layer + 1);
  }
}



void solve() {
  int n;
  cin >> n;
  AdjList adj_undirected(n+1);
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p;
    adj_undirected[p].push_back(i);
    adj_undirected[i].push_back(p);
  }
  vector<int> parents(n+1);
  AdjList adj(n+1);
  create_directed_adj(1, adj_undirected, parents, adj);

  vector<int> layer_counts(n+1);  //root is layer 0
  count_layers(1, adj, layer_counts, 0);
  PRINTVEC(layer_counts);

  long total = 1;
  long ways = 1;  //how many ways to get to one of the nodes in the current layer
  for (int layer = 1; layer <= n; layer++) {
    if (layer_counts[layer] == 0)  break;
    // transition ways from layer-1 to layer
    long possible_parents = (layer == 1) ? 1 : layer_counts[layer-1]-1;
    ways = (ways * possible_parents) % 998244353LL;
    fprintf(stderr, "layer %d: ways %lld\n", layer, ways);
    total += ways * layer_counts[layer];
    total %= 998244353LL;
  }

  cout << total << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
