#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





// Topo sort code copied from usaco.guide :)
vector<int> topo_sort(vector<vector<bool>>& adj, int n) {
  vector<int> in_degree(n+1);
  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      if (u == v)  continue;
      if (adj[u][v]) { in_degree[v]++; }
    }
  }

	std::queue<int> queue;
	for (int i = 1; i <= n; i++) {
		if (in_degree[i] == 0) { queue.push(i); }
	}
	vector<int> top_sort;
	while (!queue.empty()) {
		int curr = queue.front();
		queue.pop();
		top_sort.push_back(curr);
		for (int next = 1; next <= n; next++) {
      if (!adj[curr][next])  continue;
			if (--in_degree[next] == 0) { queue.push(next); }
		}
	}

  return top_sort;
}

class DSU {
private:
  vector<int> parents;
  vector<int> sizes;

public:
  int number_cc;
  int largest_cc;

  explicit DSU(int n) : parents(n), sizes(n, 1), number_cc(n), largest_cc(1) {
    for (int i = 0; i < n; i++)  parents[i] = i;
  }

  int find(int x) {
    return parents[x] == x ? x : (parents[x] = find(parents[x]));
  }

  bool unite(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);
    if (x_root == y_root)  return false;
    if (sizes[x_root] < sizes[y_root]) {
      swap(x_root, y_root);
    }
    sizes[x_root] += sizes[y_root];
    parents[y_root] = x_root;
    largest_cc = max(largest_cc, sizes[x_root]);
    number_cc--;
    return true;
  }

  bool connected(int x, int y) { return find(x) == find(y); }
};

void dfs_tc(vector<vector<int>>& adj_list, vector<bool>& visited, int v) {
  if (visited[v])  return;
  visited[v] = true;
  for (int u : adj_list[v]) {
    dfs_tc(adj_list, visited, u);
  }
}







void dfs_for_connectivity(vector<vector<bool>>& adj, vector<bool>& visited, int v) {
  if (visited[v])  return;
  visited[v] = true;
  for (int u = 1; u < adj.size(); u++) {
    if (adj[v][u]) {
      dfs_for_connectivity(adj, visited, u);
    }
  }
}


void solve() {
  int n;
  cin >> n;
  vector<vector<bool>> transitive_closure(n+1, vector<bool>(n+1));
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= n; j++) {
      transitive_closure[i][j] = s[j-1] == '1';
    }
  }

  // Check node can reach itself)
  for (int i = 1; i <= n; i++) {
    if (!transitive_closure[i][i]) {
      cout << "NO\n";
      return;
    }
  }
  // Check connectedness in an undirected search
  vector<vector<bool>> adj_undirected = transitive_closure;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      adj_undirected[i][j] = adj_undirected[i][j] || adj_undirected[j][i];
    }
  }
  vector<bool> visited(n+1);
  dfs_for_connectivity(adj_undirected, visited, 1);
  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      cout << "NO\n";
      return;
    }
  }

  // Check acyclic (NO LONGER A STRONG ENOUGH CHECK SINCE WE DID NOT VERIFY A PROPER TC)
  for (int i = 1; i <= n; i++) {
    for (int j = i+1; j <= n; j++) {
      if (transitive_closure[i][j] && transitive_closure[j][i]) {
        cout << "NO\n";
        return;
      }
    }
  }



  // Bottleneck: N^3 to check the transitive closure is actually transitive, and N^3 to build edges
  // Note: so far we're guaranteed that we have a semiconnected graph, and it's a DAG
  //   We don't know if the transitive closure is fully transitive but it's still a valid semiconnected DAG

  // Strategy: take 1-gap edges in topo order first (these are all guaranteed to be real edges)
  //   Then take 2-gap edges, which will be real if not already 1-gap
  //   Checking using DSU
  // Then make own copy of the transitive closure
  // And then we can compare the original transitive closure to our own at the end
  vector<int> topo_order = topo_sort(transitive_closure, n);
  if (topo_order.size() != n) {
    // Not a DAG
    cout << "NO\n";
    return;
  }
  fprintf(stderr, "Topo order: ");
  for (int x : topo_order)  fprintf(stderr, "%d ", x);
  fprintf(stderr, "\n");
  vector<pair<int, int>> edges_we_will_use;

  DSU dsu(n+1);
  for (int gap_size = 1; gap_size < n; gap_size++) {
    for (int i = 0; i + gap_size < n; i++) {
      int u = topo_order[i];
      int v = topo_order[i+gap_size];
      if (transitive_closure[u][v] && !dsu.connected(u, v)) {
        fprintf(stderr, "Adding edge %d -> %d\n", u, v);
        edges_we_will_use.push_back({u, v});
        // This edge MUST be added, so:
        if (edges_we_will_use.size() > n-1) {
          // Cycle (undirected)
          cout << "NO\n";
          return;
        }
        dsu.unite(u, v);
      }
    }
  }

  // Compare TC: build our own by dfs
  vector<vector<bool>> our_tc(n+1, vector<bool>(n+1));
  vector<vector<int>> adj_list(n+1);
  for (auto [u, v] : edges_we_will_use) {
    adj_list[u].push_back(v);
  }
  // Nx dfs in O(N)
  for (int v = 1; v <= n; v++) {
    dfs_tc(adj_list, our_tc[v], v);
  }

  // Check
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (transitive_closure[i][j] != our_tc[i][j]) {
        cout << "NO\n";
        return;
      }
    }
  }



  cout << "YES\n";
  for (auto [u, v] : edges_we_will_use) {
    cout << u << " " << v << "\n";
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