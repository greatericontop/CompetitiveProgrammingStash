#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld, ", _x); \
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













void solve() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  multiset<int> vertex_degrees;
  for (int i = 0; i < n; i++) {
    vertex_degrees.insert(adj[i].size());
  }

  int maximum = -1;
  for (int first = 0; first < n; first++) {
    int our_degree = adj[first].size();
    vertex_degrees.erase(vertex_degrees.find(our_degree));  //temporarily
    for (int neighbor : adj[first]) {
      int neighbor_degree = adj[neighbor].size();
      vertex_degrees.erase(vertex_degrees.find(neighbor_degree));  //temporarily
      vertex_degrees.insert(neighbor_degree - 1);
    }

    int degree_of_next_best = *vertex_degrees.rbegin();
    int ccs = our_degree + degree_of_next_best - 1;
    fprintf(stderr, "first=%d, ccs=%d (%d + %d)\n", first, ccs, our_degree, degree_of_next_best);
    maximum = max(maximum, ccs);

    vertex_degrees.insert(our_degree);
    for (int neighbor : adj[first]) {
      int neighbor_degree = adj[neighbor].size();
      vertex_degrees.erase(vertex_degrees.find(neighbor_degree - 1));
      vertex_degrees.insert(neighbor_degree);
    }
  }

  cout << maximum << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
