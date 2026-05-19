#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


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


/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}










void solve() {
  int n;
  cin >> n;
  AdjList adj_u(n+1);
  FORI(n-1) {
    int u, v;
    cin >> u >> v;
    adj_u[u].pb(v);
    adj_u[v].pb(u);
  }
  string labels;
  string s1;
  cin >> s1;
  labels = "#" + s1;  //1-indexed
  vector<int> parents(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(1, adj_u, parents, adj);

  bool root_is_labeled = (labels[1] != '?');
  int unlabeled_leaves = 0;
  int zero_leaves = 0, one_leaves = 0;
  int unlabeled_middles = 0;
  for (int v = 2; v <= n; v++) {
    if (adj[v].empty()) {
      if (labels[v] == '?')  unlabeled_leaves++;
      else if (labels[v] == '0')  zero_leaves++;
      else  one_leaves++;
    } else {
      if (labels[v] == '?')  unlabeled_middles++;
    }
  }

  if (root_is_labeled) {

    int ans;
    if (labels[1] == '0') {
      ans = one_leaves + ceildiv(unlabeled_leaves, 2);
    } else {
      ans = zero_leaves + ceildiv(unlabeled_leaves, 2);
    }
    cout << ans << "\n";
    return;

  } else {

    if (zero_leaves != one_leaves) {
      int ans = max(zero_leaves, one_leaves) + (unlabeled_leaves/2);
      cout << ans << "\n";
    } else {
      int ans;
      if (unlabeled_middles % 2 == 0) {
        // we unsuccessfully stall
        ans = zero_leaves + (unlabeled_leaves/2);
      } else {
        // we successfully stall
        ans = zero_leaves + ceildiv(unlabeled_leaves, 2);
      }
      cout << ans << "\n";
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
