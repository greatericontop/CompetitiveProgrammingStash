#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





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







int main() {
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
  vector<int> verts = topo_sort(transitive_closure, n);
  for (int i = 0; i < n; i++) {
    cout << verts[i] << " ";
  }


  return 0;
}