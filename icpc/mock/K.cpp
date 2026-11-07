#include <bits/stdc++.h>
using namespace std;
#define fprintf //



constexpr int INF = 676767677;

void bfs(int start, int MAXV, const vector<vector<int>>& adj, vector<int>& distances) {
  vector<bool> visited(MAXV+1, false);
  queue<int> queue;
  queue.push(start);  distances[start] = 0;
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    if (visited[v])  continue;
    visited[v] = true;

    for (int u : adj[v]) {
      distances[u] = min(distances[u], distances[v]+1);
      queue.push(u);
    }
  }
}



int main() {
  // n rows (n height)
  int n, m;  cin >> n >> m;
  int MAXV = 0;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      MAXV = max(MAXV, a[i][j]);
    }
  }

  // root node is node 0
  vector<vector<int>> adj_forward(MAXV+1);
  vector<vector<int>> adj_reverse(MAXV+1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      // make edge [i+1][j] -> [i][j]
      int v1 = i == n-1 ? 0 : a[i+1][j];
      int v2 = a[i][j];
      adj_forward[v1].push_back(v2);
      adj_reverse[v2].push_back(v1);
    }
  }

  set<int> targets;
  for (int j = 0; j < m; j++) {
    targets.insert(a[0][j]);
  }

  if (targets.size() == 1) {
    int target = *targets.begin();
    fprintf(stderr, "target = %d\n", target);

    vector<int> distances(MAXV+1, INF);
    bfs(0, MAXV+1, adj_forward, distances);
    int ans = distances[target];  assert(ans < INF);
    cout << ans << "\n";
  } else {
    assert(targets.size() == 2);
    int t1 = *targets.begin(), t2 = *targets.rbegin();

    vector<int> distances_start(MAXV+1, INF);
    bfs(0, MAXV+1, adj_forward, distances_start);
    vector<int> rev_distances_t1(MAXV+1, INF);
    bfs(t1, MAXV+1, adj_reverse, rev_distances_t1);
    vector<int> rev_distances_t2(MAXV+1, INF);
    bfs(t2, MAXV+1, adj_reverse, rev_distances_t2);
    int ans = INF;
    for (int mid = 0; mid <= MAXV; mid++) {  //mid=0 means they are both separate paths
      int shared_dist = distances_start[mid];
      int t1_dist = rev_distances_t1[mid];
      int t2_dist = rev_distances_t2[mid];
      ans = min(ans, shared_dist + t1_dist + t2_dist);
    }
    assert(ans < INF);
    cout << ans << "\n";
  }









}