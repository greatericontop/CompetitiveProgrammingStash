#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void dfs(vector<vector<bool>>& adj, vector<bool>& visited, int v) {
  if (visited[v])  return;
  visited[v] = true;
  for (int u = 1; u < adj.size(); u++) {
    if (adj[v][u]) {
      dfs(adj, visited, u);
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

  // Check valid transitive closure (must be transitive, also node can reach itself)
  for (int i = 1; i <= n; i++) {
    if (!transitive_closure[i][i]) {
      cout << "NO\n";
      return;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        if (transitive_closure[i][j] && transitive_closure[j][k] && !transitive_closure[i][k]) {
          cout << "NO\n";
          return;
        }
      }
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
  dfs(adj_undirected, visited, 1);
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

  // Build edges
  // Transitive closure entry u->v is an edge iff there's no u->k->v path
  vector<pair<int, int>> edges_we_will_use;
  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      // Edge u->v
      if (u == v)  continue;
      if (!transitive_closure[u][v])  continue;
      bool valid = true;
      for (int k = 1; k <= n; k++) {
        if (k == u || k == v) continue;
        if (transitive_closure[u][k] && transitive_closure[k][v]) {
          valid = false;
          break;
        }
      }
      if (valid) {
        edges_we_will_use.push_back({u, v});
      }
    }
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