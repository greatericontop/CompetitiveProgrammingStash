#include <bits/stdc++.h>
using namespace std;


//CODEFORCES PLEASE LET ME SUBMIT


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
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "true" : "false"); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
  #define PRINTVECB(...)
#endif
#define long int64_t
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
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









void filldepth(int v, const AdjList& adj, vector<int>& depth) {
  for (int u : adj[v]) {
    depth[u] = depth[v] + 1;
    filldepth(u, adj, depth);
  }
}
void fillsizes(int v, const AdjList& adj, vector<int>& sizes) {
  int s = 1;
  for (int u : adj[v]) {
    fillsizes(u, adj, sizes);
    s += sizes[u];
  }
  sizes[v] = s;
}


void smalltolargedp(int v, const AdjList& adj, vector<multiset<int>>& dp, const vector<int>& depths, const vector<int>& sizes, int isroot) {
  if (adj[v].empty()) {
    // for leaves, return a singleton set containing -(depth) + 2
    dp[v].insert(-depths[v] + 2);
    assert(dp[v].size() == 1);
    return;
  }

  // Small to large merge into one big set (n log^2 n)
  int largest_child_i = -1, largest_child_size = 0;
  for (int u : adj[v]) {
    smalltolargedp(u, adj, dp, depths, sizes, 2);
    if (sizes[u] > largest_child_size) {
      largest_child_size = sizes[u];
      largest_child_i = u;
    }
  }
  swap(dp[v], dp[largest_child_i]);
  for (int u : adj[v]) {
    if (u == largest_child_i)  continue;
    for (int x : dp[u]) {
      dp[v].insert(x);
    }
    dp[u].clear();
  }
  // Add self
  dp[v].insert(-depths[v]);

  // Increment highest one by 2 (or 0 if isroot==0)
  auto it = dp[v].end();  it = prev(it);
  int x = *it;
  dp[v].erase(it);
  dp[v].insert(x + isroot);
  fprintf(stderr, "final values for %d:  ", v); PRINTVEC(dp[v]);
}




void solve() {
  int n, k;
  cin >> n >> k;
  k++;
  int basecost = 2*n - 2;
  AdjList adj(n+1);
  for (int i = 2; i <= n; i++) {
    int p;  cin >> p;
    adj[p].pb(i);
  }
  vector<int> depth(n+1);
  depth[1] = 0;
  filldepth(1, adj, depth);
  vector<int> sizes(n+1);
  fillsizes(1, adj, sizes);

  vector<multiset<int>> dp(n+1);
  smalltolargedp(1, adj, dp, depth, sizes, 0);

  int tot_saving = 0;
  for (int i = 0; i < k; i++) {
    if (dp[1].empty())  break;
    auto it = dp[1].end();  it = prev(it);
    int x = *it;
    dp[1].erase(it);
    fprintf(stderr, "final DP values: %d\n", x);
    if (x >= 0) {
      tot_saving += x;
    }
  }

  cout << basecost-tot_saving << "\n";
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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
