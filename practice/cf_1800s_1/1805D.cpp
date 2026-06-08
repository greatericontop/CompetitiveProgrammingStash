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










/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}


void treedp(int v, AdjList& adj, vector<int>& longest_down, vector<int>& second_longest_down, vector<int>& longest_up) {
  int longest = -1, second_longest = -1;
  for (int child : adj[v]) {
    treedp(child, adj, longest_down, second_longest_down, longest_up);
    if (longest_down[child] >= longest) {
      second_longest = longest;
      longest = longest_down[child];
    } else if (longest_down[child] > second_longest) {
      second_longest = longest_down[child];
    }
  }
  longest_down[v] = longest + 1;
  second_longest_down[v] = second_longest + 1;
}
void treedp2(int v, AdjList& adj, vector<int>& longest_down, vector<int>& second_longest_down, vector<int>& longest_up) {
  for (int child: adj[v]) {
    int longest_up_here = longest_up[v] + 1;
    // or go down
    if (longest_down[child] == longest_down[v] - 1) {
      longest_up_here = max(longest_up_here, second_longest_down[v] + 1);
    } else {
      longest_up_here = max(longest_up_here, longest_down[v] + 1);
    }
    longest_up[child] = longest_up_here;
    treedp2(child, adj, longest_down, second_longest_down, longest_up);
  }
}


void solve() {
  int n;
  cin >> n;
  AdjList adj_undirected(n+1);
  FORI(n-1) {
    int u, v;
    cin >> u >> v;
    adj_undirected[u].pb(v);
    adj_undirected[v].pb(u);
  }
  vector<int> parents(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(1, adj_undirected, parents, adj);

  vector<int> longest_down(n+1, -1);
  vector<int> second_longest_down(n+1, -1);
  vector<int> longest_up(n+1, -1);
  longest_up[1] = 0;
  treedp(1, adj, longest_down, second_longest_down, longest_up);
  treedp2(1, adj, longest_down, second_longest_down, longest_up);
  PRINTVEC(longest_down);
  PRINTVEC(second_longest_down);
  PRINTVEC(longest_up);

  multiset<int> distances;
  FORI1(n) {
    int dist = max(longest_down[i], longest_up[i]);
    distances.insert(dist);
  }
  PRINTVEC(distances);
  vector<int> answers(n+1, -1);
  for (int k = n; k >= 1; k--) {
    while (!distances.empty() && *distances.rbegin() >= k) {
      distances.erase(prev(distances.end()));
    }
    fprintf(stderr, "k=%d, distances left %d\n", k, INT(distances.size()));
    answers[k] = min(n, INT(distances.size()) + 1);
  }

  FORI1(n) {
    cout << answers[i] << " ";
  }
  cout << "\n";




}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
