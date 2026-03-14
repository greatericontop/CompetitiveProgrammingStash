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

  assert(top_sort.size() == n); // assume it exists
  return top_sort;
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

  // Check acyclic
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

  // We will take these n-1 edges
  vector<int> topo_order = topo_sort(transitive_closure, n);

  // Now verifying transitivity is easy, just check the topo sort is right
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (!transitive_closure[topo_order[i]][topo_order[j]]) {
        cout << "NO\n";
        return;
      }
    }
  }

  vector<pair<int, int>> edges_we_will_use;
  for (int i = 0; i < n-1; i++) {
    assert(transitive_closure[topo_order[i]][topo_order[i+1]]);
    edges_we_will_use.push_back({topo_order[i], topo_order[i+1]});
  }


  if (edges_we_will_use.size() > n-1) {
    // Cycle (undirected)
    cout << "NO\n";
    return;
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