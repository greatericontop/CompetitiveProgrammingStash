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
constexpr static long MOD = 1'000'000'007LL;
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



void calc_subtree_xors(int v, const AdjList& adj, const vector<int>& a, vector<int>& subtree_xors) {
  subtree_xors[v] = a[v];
  for (int child : adj[v]) {
    calc_subtree_xors(child, adj, a, subtree_xors);
    subtree_xors[v] ^= subtree_xors[child];
  }
  fprintf(stderr, "subtree_xors[%d]=%d\n", v, subtree_xors[v]);
}





vector<long> merge(vector<long>& cur, const vector<long>& other, int expk) {
  vector<long> updated(expk, 0);
  for (int i = 0; i < expk; i++) {
    for (int j = 0; j < expk; j++) {
      updated[i ^ j] += cur[i] * other[j];
      updated[i ^ j] %= MOD;
    }
  }
  return updated;
}


long run_dp(int v, AdjList& adj, vector<int>& parents, vector<int>& subtree_xors, vector<vector<long>>& dp, const vector<int>& bspace_xors, const vector<int>& b, int k, int expk) {
  dp[v][0] = 1;
  for (int x = 1; x < expk; x++)  dp[v][x] = 0;

  for (int child : adj[v]) {
    run_dp(child, adj, parents, subtree_xors, dp, bspace_xors, b, k, expk);
    dp[v] = merge(dp[v], dp[child], expk);
  }

  // for leaves, there still could be extra
  long extra = 0;
  for (int i = 0; i < expk; i++) {
    // if we take xor of bspace_xors[i] and compare it to subtree_xors[v], if the difference is one of the b's, then include it
    int xordiff = bspace_xors[i] ^ subtree_xors[v];
    bool ok = false;
    for (int t = 0; t < k; t++) {
      if (xordiff == b[t]) {
        ok = true;
        break;
      }
    }
    if (ok) {
      extra += dp[v][i];
      extra %= MOD;
    }
  }

  fprintf(stderr, "in calculating dp[%d], there was extra %ld\n", v, extra);

  // extra has to be placed at dp[v][nothing is propagated means everything is taken]
  for (int j = 0; j < expk; j++) {
    if (subtree_xors[v] == bspace_xors[j]) {
      dp[v][j] += extra;
      dp[v][j] %= MOD;
      break;
    }
  }

  return extra;
}









void solve() {
  int n, k;
  cin >> n >> k;
  AdjList adj_undirected(n+1);
  FORI(n-1) {
    int u, v;  cin >> u >> v;
    adj_undirected[v].pb(u);
    adj_undirected[u].pb(v);
  }
  vector<int> parents(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(1, adj_undirected, parents, adj);
  vector<int> a(n+1);
  FORI1(n) {
    cin >> a[i];
  }
  PRINTVEC(a);
  vector<int> b(k);
  FORI(k) {
    cin >> b[i];
  }
  PRINTVEC(b);
  int expk = 1 << k;  //at most 16
  vector<int> bspace_xors(expk, 0);
  for (int i = 0; i < expk; i++) {
    for (int bit = 0; bit < k; bit++) {
      if (i & (1 << bit)) {
        bspace_xors[i] ^= b[bit];
      }
    }
  }
  PRINTVEC(bspace_xors);
  vector<int> subtree_xors(n+1);
  calc_subtree_xors(1, adj, a, subtree_xors);
  PRINTVEC(subtree_xors);


  vector<vector<long>> dp(n+1, vector<long>(expk));
  long ans = run_dp(1, adj, parents, subtree_xors, dp, bspace_xors, b, k, expk);

  for (int v = 1; v <= n; v++) {
    fprintf(stderr, "v=%d  ", v);  PRINTVECL(dp[v]);
  }
  cout << ans << "\n";

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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
