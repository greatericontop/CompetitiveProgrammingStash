#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECL(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:   ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECP(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%d %d],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECPL(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%lld %lld],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }










struct Vertex {
  int i;
  int j;
  int banned;

  bool operator < (const Vertex& other) const {
    if (i != other.i)  return i < other.i;
    if (j != other.j)  return j < other.j;
    return banned < other.banned;
  }
};

struct EdgeEntry {
  int i;
  int j;
  int banned;
  int weight;
};

constexpr static int INF = INT(1e8);

void solve() {
  int n, m;
  cin >> n >> m;
  vector<string> grid(n);
  for (int i = 0; i < n; i++)  cin >> grid[i];

  int start_i = INT_MIN, start_j = INT_MIN, target_i = INT_MIN, target_j = INT_MIN;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'S') {
        start_i = i;
        start_j = j;
      } else if (grid[i][j] == 'T') {
        target_i = i;
        target_j = j;
      }
    }
  }

  // 0, 1, 2, 3 = no up, down, left, right
  vector<vector<vector<vector<EdgeEntry>>>> adj(n, vector<vector<vector<EdgeEntry>>>(m, vector<vector<EdgeEntry>>(4)));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int banned = 0; banned < 4; banned++) {
        if (grid[i][j] == '#')  continue;
        // adj[i][j][banned]
        // Up
        if (banned != 0 && i >= 1 && grid[i-1][j] != '#') {
          adj[i][j][banned].pb({i-1, j, 0, 1});
          if (i >= 2 && grid[i-2][j] != '#') {
            adj[i][j][banned].pb({i-2, j, 0, 2});
            if (i >= 3 && grid[i-3][j] != '#')  adj[i][j][banned].pb({i-3, j, 0, 3});
          }
        }
        // Down
        if (banned != 1 && i <= n-2 && grid[i+1][j] != '#') {
          adj[i][j][banned].pb({i+1, j, 1, 1});
          if (i <= n-3 && grid[i+2][j] != '#') {
            adj[i][j][banned].pb({i+2, j, 1, 2});
            if (i <= n-4 && grid[i+3][j] != '#')  adj[i][j][banned].pb({i+3, j, 1, 3});
          }
        }
        // Left
        if (banned != 2 && j >= 1 && grid[i][j-1] != '#') {
          adj[i][j][banned].pb({i, j-1, 2, 1});
          if (j >= 2 && grid[i][j-2] != '#') {
            adj[i][j][banned].pb({i, j-2, 2, 2});
            if (j >= 3 && grid[i][j-3] != '#')  adj[i][j][banned].pb({i, j-3, 2, 3});
          }
        }
        // Right
        if (banned != 3 && j <= m-2 && grid[i][j+1] != '#') {
          adj[i][j][banned].pb({i, j+1, 3, 1});
          if (j <= m-3 && grid[i][j+2] != '#') {
            adj[i][j][banned].pb({i, j+2, 3, 2});
            if (j <= m-4 && grid[i][j+3] != '#')  adj[i][j][banned].pb({i, j+3, 3, 3});
          }
        }
      }
    }
  }


  vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(4, false)));
  map<Vertex, int> distances;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int b = 0; b < 4; b++) {
        distances[{i, j, b}] = INF;
      }
    }
  }
  set<pair<int, Vertex>> frontier;

  for (int b = 0; b < 4; b++) {
    distances[{start_i, start_j, b}] = 0;
    frontier.insert({0, {start_i, start_j, b}});
  }

  while (!frontier.empty()) {
    auto [dist, v] = *frontier.begin();
    fprintf(stderr, "popped frontier: vertex{%d, %d, %d} dist %d\n", v.i, v.j, v.banned, dist);
    frontier.erase(frontier.begin());
    visited[v.i][v.j][v.banned] = true;

    for (EdgeEntry ee : adj[v.i][v.j][v.banned]) {
      int new_dist = dist + ee.weight;
      Vertex ee_v = {ee.i, ee.j, ee.banned};
      int cur_dist = distances[ee_v];
      if (new_dist < cur_dist) {
        distances[ee_v] = new_dist;
        frontier.erase({cur_dist, ee_v});
        frontier.insert({new_dist, ee_v});
      }
    }
  }


  int ans = INF;
  for (int b = 0; b < 4; b++) {
    ans = min(ans, distances[{target_i, target_j, b}]);
  }

  if (ans == INF)  ans = -1;
  cout << ans << "\n";

}









int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
