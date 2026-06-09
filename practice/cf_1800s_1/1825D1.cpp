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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









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


void perform_twocolor(int v, AdjList& adj, vector<bool>& twocolor) {
  for (int child : adj[v]) {
    twocolor[child] = !twocolor[v];
    perform_twocolor(child, adj, twocolor);
  }
}



void solve() {
  int n, k;
  cin >> n >> k;
  AdjList adj_undirected(n+1);
  FORI(n - 1) {
    int u, v;
    cin >> u >> v;
    adj_undirected[u].pb(v);
    adj_undirected[v].pb(u);
  }
  vector<int> parents(n+1, -1);
  AdjList adj(n+1);
  create_directed_adj(1, adj_undirected, parents, adj);
  vector<bool> twocolor(n+1);
  twocolor[1] = true;
  perform_twocolor(1, adj, twocolor);
  long red = 0, blue = 0;
  FORI1(n) {
    if (twocolor[i])  red++;
    else  blue++;
  }

  if (k == 1 || k == 3) {
    cout << 1 << "\n";
  } else {
    // k is 2
    fprintf(stderr, "red = %lld, blue = %lld\n", red, blue);
    long combinations_that_are_even = red * (red-1) / 2  +  blue * (blue-1) / 2;
    long total_combinations = LONG(n) * LONG(n-1) / 2;
    long numerator = total_combinations + combinations_that_are_even;
    long ans = (numerator * modular_inverse(total_combinations)) % MOD;
    cout << ans << "\n";
  }
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
