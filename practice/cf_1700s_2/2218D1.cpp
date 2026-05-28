#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", INT(_x)); \
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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









void dfs(int v, const AdjList& adj, vector<bool>& good_nodes) {
  // acyclic guaranteed
  good_nodes[v] = true;
  for (int u : adj[v]) {
    dfs(u, adj, good_nodes);
  }
}


void solve() {
  int n; long k;
  cin >> n >> k;
  vector<long> positions(n);  //come presorted
  FORI(n)  cin >> positions[i];
  vector<long> delays(n);
  FORI(n)  cin >> delays[i];
  int q;
  cin >> q;
  vector<long> queries(q);
  FORI(q)  cin >> queries[i];

  vector<bool> good_nodes(2*n, false);
  AdjList adj(2*n);
  for (int i = 0; i < n; i++) {
    int initial_time = delays[i];
    // node 2i, going left
    int j = i-1;
    for (; j >= 0; j--) {
      assert((initial_time + (positions[i] - positions[j])) >= 0);
      long time_at_j = (initial_time + (positions[i] - positions[j])) % k;
      if (time_at_j == delays[j]) {
        break;
      }
    }
    if (j == -1) {
      good_nodes[2*i] = true;
    } else {
      //adj[2*i] = 2*j+1;  //going right
      adj[2*j+1].pb(2*i);
    }

    j = i+1;
    for (; j < n; j++) {
      assert((initial_time + (positions[j] - positions[i])) >= 0);
      long time_at_j = (initial_time + (positions[j] - positions[i])) % k;
      if (time_at_j == delays[j]) {
        break;
      }
    }
    if (j == n) {
      good_nodes[2*i+1] = true;
    } else {
      //adj[2*i+1] = 2*j;
      fprintf(stderr, "going right at node i=%d, gets to node j=%d\n", i, j);
      adj[2*j].pb(2*i+1);
    }
  }
  // dfs from end nodes
  vector<int> dfs_sources;
  for (int i = 0; i < 2*n; i++) {
    if (good_nodes[i]) {
      dfs_sources.pb(i);
    }
  }
  for (int v : dfs_sources) {
    dfs(v, adj, good_nodes);
  }
  PRINTVEC(good_nodes);



  for (long query : queries) {
    int stopped_light = -1;
    for (int i = 0; i < n; i++) {
      if (positions[i] < query)  continue;
      assert((positions[i] - query) >= 0);
      long time_at_i = (positions[i] - query) % k;
      if (time_at_i == delays[i]) {
        stopped_light = i;
        break;
      }
    }
    fprintf(stderr, "query %d, stopped_light %d\n", query, stopped_light);
    if (stopped_light == -1) {
      cout << "YES\n";
    } else {
      int node = 2*stopped_light;  //moving left
      if (good_nodes[node]) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }


  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
