#include <bits/stdc++.h>
using namespace std;



#pragma GCC optimize("Ofast")

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


// void check_easy(int v, const AdjList& adj, vector<long>& dp, vector<long>& a, vector<long>& limits) {
//   long usages_required_here = a[v] - limits[v];
//   for (int child : adj[v]) {
//     check_easy(child, adj, dp, a, limits);
//     usages_required_here += dp[child];
//   }
//   dp[v] = max<long>(usages_required_here, 0);
// }
vector<long> fill(int n, long k) {
  long base = k / n;
  long extra = k % n;
  vector<long> limits(n+1, base);
  for (int i = 1; i <= extra; i++) {
    limits[i]++;
  }
  return limits;
}


struct StateHard {
  long even;
  long odd;

  /* Merge two states and pull out lowest even/odd values */
  void combine(const StateHard& other) {
    long a = even+other.even, b = even+other.odd, c = odd+other.even, d = odd+other.odd;
    even = LLONG_MAX;  odd = LLONG_MAX;
    for (long x : {a, b, c, d}) {
      if (x % 2 == 0)  even = min(even, x);
      else  odd = min(odd, x);
    }
    // so if we only have evens for example, we'll put odd as the same value
    if (even == LLONG_MAX)  even = odd;
    if (odd == LLONG_MAX)  odd = even;
  }

  void relu() {
    if (even % 2 == 0)  even = max<long>(even, 0);
    else  even = max<long>(even, 1);  //e.g., -35 becomes +1
    if (odd % 2 == 0)  odd = max<long>(odd, 0);
    else  odd = max<long>(odd, 1);
  }
};
void check_hard(int v, const AdjList& adj, vector<StateHard>& dp, vector<long>& a, vector<long>& limits) {
  StateHard s = {a[v] - limits[v], a[v] - limits[v]};
  for (int child : adj[v]) {
    check_hard(child, adj, dp, a, limits);
    s.combine(dp[child]);
  }
  s.relu();
  dp[v] = s;
}












void solve() {
  int n, root;
  cin >> n >> root;
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];
  AdjList adj_undirected(n+1);
  FORI(n-1) {
    int u, v;  cin >> u >> v;
    adj_undirected[u].pb(v);
    adj_undirected[v].pb(u);
  }
  vector<int> parents(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(root, adj_undirected, parents, adj);

  long sum_a = accumulate(a.begin(), a.end(), 0LL);
  // find the minimum k such that we have enough *power*
  long best = LLONG_MAX;
  for (int res = 0; res < 2*n; res++) {  // ... mod 2n
    if ((sum_a % 2) != (res % 2))  continue;  //prune early when parity does not match
    // theoretically, if all nodes are >=1e9, then each node can propagate up at most 1, so this should be plenty
    long l = 0, r = 600'000'000;  //1.2e9
    while (l < r) {
      long mid = l + (r-l)/2;
      long k = mid*2*n + res;
      vector<long> limits = fill(n, k);
      vector<StateHard> dp(n+1);
      check_hard(root, adj, dp, a, limits);
      if (dp[root].even == 0 || dp[root].odd == 0) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    best = min(best, l*2*n + res);
  }
  if (best == LLONG_MAX) {
    cout << "-1\n";
    return;
  } else {
    cout << best << "\n";
    return;
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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
