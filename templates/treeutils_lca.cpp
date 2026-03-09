#include <bits/stdc++.h>
using namespace std;





using AdjList = vector<vector<int>>;
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}

/* Corresponding to first & last appearances of a vertex */
using LCAEulerTour = vector<pair<int, int>>;
/* tour[v].first = height, tour[v].second = v. RMQ on min height. */
using LCADepthTour = vector<pair<int, int>>;

void run_lca_tour(int v, AdjList& adj, LCADepthTour& tour, LCAEulerTour& euler_tour, int& counter, int height) {
  tour.push_back({height, v});
  euler_tour[v].first = counter;
  counter++;
  for (int child : adj[v]) {
    run_lca_tour(child, adj, tour, euler_tour, counter, height+1);
    tour.push_back({height, v});
    euler_tour[v].second = counter;
    counter++;
  }
  if (adj[v].empty()) {
    euler_tour[v].second = counter - 1;
  }
}


#define exp(x) (1 << (x))
class LCASegmentTree {
private:
  int max_layer;
  int n;
  vector<vector<pair<int, int>>> segments; // segments[l] contains 0 to 2^l - 1

public:
  explicit LCASegmentTree(int max_layer, LCADepthTour lcatour) : max_layer(max_layer), n(exp(max_layer)), segments(max_layer + 1) {
    segments[0] = vector<pair<int, int>>(n, {INT_MAX, INT_MAX});
    assert(lcatour.size() <= n);
    for (int i = 0; i < lcatour.size(); i++) {
      segments[0][i] = lcatour[i];
    }

    for (int layer = 1; layer <= max_layer; layer++) {
      for (int i = 0; i < exp(max_layer-layer); i++) {
        segments[layer].push_back(min(segments[layer-1][2*i], segments[layer-1][2*i+1]));
      }
    }
  }

  void point_update(int i, pair<int, int> new_value) {
    segments[0][i] = new_value;
    for (int layer = 1; layer <= max_layer; layer++) {
      i /= 2;
      segments[layer][i] = min(segments[layer-1][2*i], segments[layer-1][2*i+1]);
    }
  }

  /* Range query left to right inclusive, 0-indexed */
  pair<int, int> range_query(int left, int right) {
    pair<int, int> answer = {INT_MAX, INT_MAX};
    while (left <= right) {
      // Find biggest interval (aka what's the biggest power of 2 that divides a)
      int layer_i = left;
      int layer = 0;
      while ((left % (2 << layer) == 0) && (layer < 18) && (left + (2 << layer) - 1 <= right)) {
        layer++;
        layer_i /= 2;
      }
      answer = min(answer, segments[layer][layer_i]);
      left += exp(layer);
    }
    return answer;
  }
};





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

  LCAEulerTour lca_euler_tour(n);
  LCADepthTour lca_depth_tour;
  int counter = 0;
  run_lca_tour(0, adj, lca_depth_tour, lca_euler_tour, counter, 0);

  printf("LCA tour list:\n");
  for (auto [height, v] : lca_depth_tour) {
    printf("%d ", v);
  }
  printf("\n");
  printf("Euler tour:\n");
  for (int v = 0; v < n; v++) {
    printf("%d: %d to %d\n", v, lca_euler_tour[v].first, lca_euler_tour[v].second);
  }

  LCASegmentTree lca_segment_tree(5, lca_depth_tour);
  vector<pair<int, int>> queries = {
      {0, 1}, // should be 0
      {1, 2}, // should be 0
      {4, 5}, // should be 2
      {6, 7}, // should be 3
      {4, 6}, // should be 0
  };
  for (auto [u, v] : queries) {
    int left = min(lca_euler_tour[u].first, lca_euler_tour[v].first);
    int right = max(lca_euler_tour[u].first, lca_euler_tour[v].first);
    pair<int, int> lca_info = lca_segment_tree.range_query(left, right);
    printf("LCA of %d and %d is %d\n", u, v, lca_info.second);
  }

}