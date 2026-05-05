#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG
#define MAYBE_WRONG_APPROACH


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
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
#define long long long
#define pb push_back
using pairii = pair<int, int>;
using pairll = pair<long, long>;







vector<int> toposort(int n, vector<vector<int>>& graph) {
  vector<int> in_degree(n);
  for (const vector<int> &nodes : graph) {
    for (int node : nodes) { in_degree[node]++; }
  }

  std::queue<int> queue;
  for (int i = 0; i < n; i++) {
    if (in_degree[i] == 0) { queue.push(i); }
  }
  vector<int> top_sort;
  while (!queue.empty()) {
    int curr = queue.front();
    queue.pop();
    top_sort.push_back(curr);
    for (int next : graph[curr]) {
      if (--in_degree[next] == 0) { queue.push(next); }
    }
  }

  return top_sort;
}




void solve() {
  int n;
  cin >> n;
  int indexof_1 = -1;
  vector<int> c(n);
  for (int i = 0; i < n; i++) {
    cin >> c[i];
    if (c[i] == 1)  indexof_1 = i;
  }
  if (indexof_1 == -1) {
    cout << "NO\n";
    return;
  }

  vector<int> top_indices;
  top_indices.pb((n-indexof_1)%n);
  vector<pairii> dag_edges;

  for (int i1 = 1; i1 < n; i1++) {
    int i = (indexof_1 + i1) % n;
    fprintf(stderr, "i = %d, top indices:  ", i);
    for (int x : top_indices)  fprintf(stderr, "%d ", x);
    fprintf(stderr, "\n");
    int c_prev = c[(i-1+n) % n];
    int c_i = c[i % n];
    if (c_i == c_prev + 1) {
      // cur < prev
      dag_edges.pb({ (n-i)%n, (n-i+1)%n });
      top_indices.pb( (n-i)%n );
    } else if (c_i < 2 || c_i > c_prev + 1) {
      cout << "NO\n";
      return;
    } else {
      // Trim stack to size c_i - 1
      int last_deleted_i;
      while (top_indices.size() > c_i - 1) {
        last_deleted_i = top_indices.back();
        top_indices.pop_back();
      }
      dag_edges.pb({ (n-i)%n, top_indices.back() });
      dag_edges.pb({ last_deleted_i, (n-i)%n });
      top_indices.pb( (n-i)%n );
    }
  }

  for (auto & [x, y] : dag_edges) {
    fprintf(stderr, "DAG: %d < %d\n", x, y);
  }

#ifdef MAYBE_WRONG_APPROACH
  cout << "YES\n";
#else
  vector<vector<int>> adj(n);
  for (auto & [x, y] : dag_edges) {
    adj[x].pb(y);
  }
  vector<int> topo_order = toposort(n, adj);
  if (topo_order.size() != n) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
#endif

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
