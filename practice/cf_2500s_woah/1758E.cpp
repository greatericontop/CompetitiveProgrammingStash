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
constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;







struct EdgeEntry {
  int target;
  int delta;
};
void dfs(int v, const vector<vector<EdgeEntry>>& adj, vector<int>& values, vector<bool>& visited, int h) {
  visited[v] = true;
  for (const auto [u, delta] : adj[v]) {
    if (visited[u])  continue;
    values[u] = (values[v] + delta) % h;
    dfs(u, adj, values, visited, h);
  }
}
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




void solve() {
  int n, m, h;
  cin >> n >> m >> h;
  vector<vector<int>> a(n+1, vector<int>(m+1));
  FORI1(n) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  long ans = 1;
  int exponent = 0;
  // note: graph will be in m, so each row

  // free rows
  for (int i = 1; i <= n; i++) {
    bool free = true;
    for (int j = 1; j <= m; j++) {
      if (a[i][j] != -1) {
        free = false;
        break;
      }
    }
    if (free) {
      exponent++;
    }
  }

  // graph making
  vector<vector<EdgeEntry>> adj(m+1);
  for (int i = 1; i <= n; i++) {
    vector<int> indices;
    for (int j = 1; j <= m; j++) {
      if (a[i][j] != -1) {
        indices.pb(j);
      }
    }

    for (int j = 0; j < INT(indices.size()) - 1; j++) {
      int u = indices[j];
      int v = indices[j+1];
      adj[u].pb(EdgeEntry{v, (a[i][v] - a[i][u] + h) % h});
      adj[v].pb(EdgeEntry{u, (a[i][u] - a[i][v] + h) % h});
    }
  }

  vector<int> values(m+1, -1);
  vector<bool> visited(m+1, false);
  exponent--;  //first one doesn't count
  for (int v = 1; v <= m; v++) {
    if (visited[v])  continue;
    assert(values[v] == -1);
    values[v] = 0;
    exponent++;
    dfs(v, adj, values, visited, h);
  }

  // confirm
  bool correct = true;
  for (int v = 1; v <= m; v++) {
    for (const auto [u, delta] : adj[v]) {
      int actual_delta = (values[u] - values[v] + h) % h;
      if (actual_delta != delta) {
        correct = false;
        break;
      }
    }
  }

  ans = mod_exp(h, exponent);
  if (!correct)  ans = 0;
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
