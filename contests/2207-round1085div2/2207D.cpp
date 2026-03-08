#include <bits/stdc++.h>
using namespace std;
#define long long long

#define INT_BIG (100000000)
//#define fprintf(...) // no-op





// you should make this a template later
void create_directed_adj(int v, vector<vector<int>>& adj_undirected, vector<int>& parents, vector<vector<int>>& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}


void best_2_downward_distances(int v, vector<vector<int>>& adj,
                               vector<pair<int, int>>& best_down_dists, vector<pair<int, int>>& best_down_dists_sources) {
  int best = INT_BIG;
  int second_best = INT_BIG;
  int best_source = -1;
  int second_best_source = -1;
  if (adj[v].empty()) {
    best_down_dists[v] = {0, 0};
    best_down_dists_sources[v] = {-1, -1};
    return;
  }
  for (int child : adj[v]) {
    best_2_downward_distances(child, adj, best_down_dists, best_down_dists_sources);
    int dist = best_down_dists[child].first + 1; // can only use one from each child
    if (dist < best) {
      second_best = best;
      second_best_source = best_source;
      best = dist;
      best_source = child;
    } else if (dist < second_best) {
      second_best = dist;
      second_best_source = child;
    }
  }
  best_down_dists[v] = {best, second_best};
  best_down_dists_sources[v] = {best_source, second_best_source};
}


void best_upward_distances(int v, vector<int>& parents, vector<vector<int>>& adj,
                           vector<pair<int, int>>& best_down_dists, vector<pair<int, int>>& best_down_dists_sources, vector<int>& best_up_dists) {
  if (parents[v] == -1) {
    best_up_dists[v] = INT_BIG;
  } else {
    int best_up_distance = INT_BIG;
    int parent = parents[v];
    if (best_down_dists_sources[parent].first != v) { // can only use best if it doesn't just loop back to us
      best_up_distance = min(best_up_distance, best_down_dists[parent].first + 1);
    } else { // otherwise we can always use the second best
      best_up_distance = min(best_up_distance, best_down_dists[parent].second + 1);
    }
    best_up_distance = min(best_up_distance, best_up_dists[parent] + 1);
    best_up_dists[v] = best_up_distance;
  }

  for (int child : adj[v]) {
    best_upward_distances(child, parents, adj, best_down_dists, best_down_dists_sources, best_up_dists);
  }
}





void solve() {
  int n, k, root;
  cin >> n >> k >> root;
  vector<vector<int>> adj_undirected(n+1);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    adj_undirected[a].push_back(b);
    adj_undirected[b].push_back(a);
  }
  vector<int> parents(n+1);
  vector<vector<int>> adj(n+1);
  parents[root] = -1;
  create_directed_adj(root, adj_undirected, parents, adj);

  fprintf(stderr, "Creating tree rooted at %d with adj:\n", root);
  for (int i = 1; i <= n; i++) {
    fprintf(stderr, "%d: ", i);
    for (int child : adj[i])  fprintf(stderr, "%d ", child);
    fprintf(stderr, "   parent: %d\n", parents[i]);
  }



  vector<pair<int, int>> best_down_dists(n+1, {INT_BIG, INT_BIG});
  vector<pair<int, int>> best_down_dists_sources(n+1, {-1, -1});
  best_2_downward_distances(root, adj, best_down_dists, best_down_dists_sources);

  fprintf(stderr, "Best downward distances:\n");
  for (int i = 1; i <= n; i++) {
    fprintf(stderr, "%d: %d, %d  (from %d, %d)\n", i, best_down_dists[i].first, best_down_dists[i].second, best_down_dists_sources[i].first, best_down_dists_sources[i].second);
  }



  vector<int> best_up_dists(n+1, INT_BIG);
  best_upward_distances(root, parents, adj, best_down_dists, best_down_dists_sources, best_up_dists);

  fprintf(stderr, "Best upward distances:\n");
  for (int i = 1; i <= n; i++) {
    fprintf(stderr, "%d: %d\n", i, best_up_dists[i]);
  }


}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}