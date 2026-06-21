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






struct DPEntry {
  int cost;
  int mink;
};


void trav(int v, const AdjList& adj, vector<DPEntry>& dp, int H) {
  if (adj[v].empty()) {
    dp[v] = {0, 0};
    return;
  }

  int totalcost = 0;
  int max_mink = -1;
  for (int u : adj[v]) {
    trav(u, adj, dp, H);
    if (H-1 < dp[u].mink) {
      totalcost += dp[u].cost + 1;
    } else {
      totalcost += dp[u].cost;
    }
    if (dp[u].mink != H) {
      max_mink = max(max_mink, dp[u].mink);
    }
  }
  dp[v] = {totalcost, max_mink + 1};
}


/* Operations required to cut all subtrees to height H */
int calc_operations(int n, const AdjList& adj, int H) {
  int H_subtree = H-1;
  vector<DPEntry> dp(n+1);
  trav(1, adj, dp, H_subtree);
  int totalcost = 0;
  for (int u : adj[1]) {
    totalcost += dp[u].cost;
  }
  fprintf(stderr, "for tree height %d, total cost is %d\n", H, totalcost);
  return totalcost;
}


void solve() {
  int n, max_ops;
  cin >> n >> max_ops;
  AdjList adj(n+1);
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p;
    adj[p].pb(i);
  }

  int l = 1, r = n;
  while (l < r) {
    int try_height = l + (r-l)/2;
    int cost = calc_operations(n, adj, try_height);
    if (cost <= max_ops) {
      r = try_height;
    } else {
      l = try_height + 1;
    }
  }

  cout << l << "\n";

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
