#include <bits/stdc++.h>
using namespace std;
using AdjList = vector<vector<int>>;






/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}


//int n;
//cin >> n;
//AdjList adj_undirected(n+1);
//FORI(n-1) {
//int u, v;  cin >> u >> v;
//adj_undirected[u].pb(v);
//adj_undirected[v].pb(u);
//}
//vector<int> parents(n+1, -1);
//AdjList adj(n+1);
//create_directed_adj(1, adj_undirected, parents, adj);


/* tour[v].first corresponds to v, tour[v].second corresponds to the last endpoint of the segment, inclusive. */
using EulerTour = vector<pair<int, int>>;

void euler_tour(int v, AdjList& adj, EulerTour& tour, int& counter) {
  tour[v].first = counter;
  counter++;
  for (int child : adj[v]) {
    euler_tour(child, adj, tour, counter);
  }
  tour[v].second = counter - 1;
}





int main() {
  int n = 8;
  vector<pair<int, int>> edges = {
      {0, 1},
      {0, 2},
      {0, 3},
      {2, 4},
      {2, 5},
      {3, 6},
      {3, 7},
  };
  AdjList adj_undirected(n);
  for (auto [u, v]: edges) {
    adj_undirected[u].push_back(v);
    adj_undirected[v].push_back(u);
  }
  vector<int> parents(n);
  AdjList adj(n);
  create_directed_adj(0, adj_undirected, parents, adj);

  for (int v = 0; v < n; v++) {
    printf("%d:", v);
    for (int child : adj[v]) {
      printf(" %d", child);
    }
    printf(" (parent %d)\n", parents[v]);
  }

  EulerTour tour(n);
  int counter = 0;
  euler_tour(0, adj, tour, counter);
  for (int v = 0; v < n; v++) {
    printf("tour[%d] = %d to %d\n", v, tour[v].first, tour[v].second);
  }

}