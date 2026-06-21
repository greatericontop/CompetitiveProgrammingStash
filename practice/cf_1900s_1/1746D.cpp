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









void traverse(int v, const AdjList& adj, vector<int>& floorcounts, vector<long>& dp, vector<long>& extra, const vector<long>& s) {
  if (adj[v].empty()) {
    dp[v] = s[v] * floorcounts[v];
    extra[v] = s[v];
    return;
  }
  dp[v] = s[v] * floorcounts[v];
  int floorcount_of_children = floorcounts[v] / INT(adj[v].size());
  vector<long> extras;
  for (int u : adj[v]) {
    floorcounts[u] = floorcount_of_children;
    traverse(u, adj, floorcounts, dp, extra, s);
    dp[v] += dp[u];
    extras.pb(extra[u]);
  }
  sort(extras.begin(), extras.end(), greater<long>());
  int rem = floorcounts[v] % INT(adj[v].size());
  for (int i = 0; i < rem; i++) {
    dp[v] += extras[i];
  }
  extra[v] = extras[rem] + s[v];
}


void solve() {
  int n, k;
  cin >> n >> k;
  AdjList adj(n+1);
  for (int v = 2; v <= n; v++) {
    int p;
    cin >> p;
    adj[p].pb(v);
  }
  vector<long> s(n+1);
  FORI1(n)  cin >> s[i];

  vector<int> floorcounts(n+1);
  floorcounts[1] = k;
  vector<long> dp(n+1);
  vector<long> extra(n+1);
  traverse(1, adj, floorcounts, dp, extra, s);

  PRINTVEC(floorcounts);
  PRINTVECL(dp);
  PRINTVECL(extra);
  cout << dp[1] << "\n";

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
