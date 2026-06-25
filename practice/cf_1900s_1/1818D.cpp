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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;








void dfs(int v, int starter1, int starter2, const AdjList& adj, vector<int>& parent) {
  for (int u : adj[v]) {
    if (v == starter2 && u == starter1)  continue;  //not allowed to go from starter2 to starter1
    if (parent[u] != -1)  continue;
    parent[u] = v;
    dfs(u, starter1, starter2, adj, parent);
  }
}


void solve() {
  int n, m;
  cin >> n >> m;
  AdjList adj(n+1);
  FORI(m) {
    int u, v;
    cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  for (int starter = 1; starter <= n; starter++) {
    if (adj[starter].size() < 4)  continue;
    // see if there is a cycle. perform max m dfs
    for (int v : adj[starter]) {
      vector<int> parent(n+1, -1);
      parent[v] = starter;
      dfs(v, starter, v, adj, parent);
      if (parent[starter] != -1) {
        // found a cycle
        vector<int> cycle;
        cycle.pb(starter);
        int cur = parent[starter];
        while (cur != starter) {
          cycle.pb(cur);
          cur = parent[cur];
        }
        cycle.pb(starter);
        assert(cycle.size() >= 4 && cycle.front() == cycle.back());  //a triangle would have 4 entries
        int not1 = cycle[1], not2 = cycle[cycle.size()-2];
        int alt1 = -1, alt2 = -1;
        for (int u : adj[starter]) {
          if (u != not1 && u != not2) {
            if (alt1 == -1) { alt1 = u; }
            else  { alt2 = u; break; }
          }
        }
        assert(alt1 != -1 && alt2 != -1);
        fprintf(stderr, "found cycle: alt1=%d, alt2=%d\n  ", alt1, alt2);
        PRINTVEC(cycle);
        auto it1 = find(cycle.begin(), cycle.end(), alt1);
        auto it2 = find(cycle.begin(), cycle.end(), alt2);
        if (it1-cycle.begin() > it2-cycle.begin()) {
          swap(it1, it2);
          swap(alt1, alt2);
        }
        assert((it1 == cycle.end() || (*it1 != not1 && *it1 != not2)) && (it2 == cycle.end() || (*it2 != not1 && *it2 != not2)));
        fprintf(stderr, "it1 points to %ld, it2 points to %ld\n", it1-cycle.begin(), it2-cycle.begin());
        vector<pairii> edges;
        if (it1 == cycle.end() && it2 == cycle.end()) {
          edges.pb({starter, alt1});
          edges.pb({starter, alt2});
          for (int i = 0; i+1 < cycle.size(); i++) {
            edges.pb({cycle[i], cycle[(i+1)]});
          }
        } else if (it2 == cycle.end()) {
          edges.pb({starter, alt2});
          edges.pb({starter, cycle[cycle.size()-2]});
          for (auto it = cycle.begin(); it != it1; it++) {
            edges.pb({*it, *(it+1)});
          }
          edges.pb({*it1, starter});
        } else {
          for (auto it = cycle.begin(); it != it1; it++) {
            edges.pb({*it, *(it+1)});
          }
          edges.pb({*it1, starter});
          edges.pb({starter, *it2});
          edges.pb({starter, cycle[cycle.size()-2]});
        }

        cout << "YES\n";
        cout << edges.size() << "\n";
        int starter_appearances = 0;
        for (int i = 0; i < edges.size(); i++) {
          assert(edges[i].first != edges[i].second);
          assert(adj[edges[i].first].end() != find(adj[edges[i].first].begin(), adj[edges[i].first].end(), edges[i].second));
          if (edges[i].first == starter || edges[i].second == starter) {
            starter_appearances++;
          }
          cout << edges[i].first << " " << edges[i].second << "\n";
        }
        assert(starter_appearances == 4);
        cout << "\n";
        return;
      }

    }
  }

  cout << "NO\n";

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
