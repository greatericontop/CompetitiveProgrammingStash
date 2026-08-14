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
constexpr static long MOD =   998'244'353LL;
/* O(log exp) */
int64_t mod_exp(int64_t base, int64_t exp) {
  int64_t result = 1;
  while (exp > 0) {
    if (exp & 1)  result = (result * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

/* Only works for primes, O(log MOD) */
int64_t modular_inverse(int64_t a) {
  return mod_exp(a, MOD - 2);
}

/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}




/*
 * Nonempty strongly good subtrees rooted at :v:
 */
void dp_strongly_good(int v, AdjList& adj, vector<long>& strongly_good) {
  if (adj[v].empty()) {
    strongly_good[v] = 1;
    return;
  }
  // no root, combinations of children
  long childrenct = 1;
  for (int child : adj[v]) {
    dp_strongly_good(child, adj, strongly_good);
    childrenct *= (strongly_good[child] + 1);  //including empty
    childrenct %= MOD;
  }
  strongly_good[v] = (childrenct + MOD) % MOD;  //-1 to remove completely empty, +1 for just the root
}

/*
 * Nonempty weakly good subtrees
 */
void dp_weakly_good(int v, AdjList& adj, const vector<long>& strongly_good, vector<long>& weakly_good) {
  if (adj[v].empty()) {
    weakly_good[v] = 1;
    return;
  }

  // Select root -> one strongly good subtree
  long selectroot = 1;  //or zero
  for (int child : adj[v]) {
    dp_weakly_good(child, adj, strongly_good, weakly_good);
    selectroot += strongly_good[child];
    selectroot %= MOD;
  }

  // Don't select root
  // 1 nonempty weakly good subtree
  long ct1 = 0;
  for (int child : adj[v]) {
    ct1 += weakly_good[child];
    ct1 %= MOD;
  }
  // 2 different nonempty strongly good subtrees
  long total_strongly_good_children = 0;
  for (int child : adj[v]) {
    total_strongly_good_children += strongly_good[child];
    total_strongly_good_children %= MOD;
  }
  long ct2 = 0;
  for (int child : adj[v]) {
    long other_children = (total_strongly_good_children - strongly_good[child] + MOD) % MOD;
    ct2 += (strongly_good[child] * other_children) % MOD;
    ct2 %= MOD;
  }
  ct2 = (ct2 * modular_inverse(2)) % MOD;

  weakly_good[v] = (selectroot + ct1 + ct2) % MOD;
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
  AdjList adj(n+1);
  vector<int> parents(n+1, -1);
  create_directed_adj(1, adj_undirected, parents, adj);

  vector<long> strongly_good(n+1, -1);
  dp_strongly_good(1, adj, strongly_good);
  vector<long> weakly_good(n+1, -1);
  dp_weakly_good(1, adj, strongly_good, weakly_good);
  cout << (weakly_good[1]+1) << "\n";  //finally, completely empty
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
