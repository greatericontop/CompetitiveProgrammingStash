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
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









/*
 * DSU
 * Code mostly copied from USACO Guide, with a few extra features added in
 */
class DSU {
private:
  vector<int> parents;
  vector<int> sizes;

public:
  int number_cc;
  int largest_cc;

  explicit DSU(int n) : parents(n), sizes(n, 1), number_cc(n), largest_cc(1) {
    for (int i = 0; i < n; i++)  parents[i] = i;
  }

  int find(int x) {
    return parents[x] == x ? x : (parents[x] = find(parents[x]));
  }

  bool unite(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);
    if (x_root == y_root)  return false;
    if (sizes[x_root] < sizes[y_root]) {
      swap(x_root, y_root);
    }
    sizes[x_root] += sizes[y_root];
    parents[y_root] = x_root;
    largest_cc = max(largest_cc, sizes[x_root]);
    number_cc--;
    return true;
  }

  bool connected(int x, int y) { return find(x) == find(y); }
};


struct AdjEntry {
  int to;
  bool type;  //false = same, true = flipped
};


void dfs(int v, const vector<vector<AdjEntry>>& adj, vector<bool>& visited, vector<bool>& settings) {
  if (visited[v])  return;
  visited[v] = true;
  for (const auto [u, type] : adj[v]) {
    if (visited[u])  assert(settings[u] == (settings[v] ^ type));
    settings[u] = settings[v] ^ type;
    dfs(u, adj, visited, settings);
  }
}


void solve() {
  int n;
  cin >> n;
  vector<vector<int>> A(n+1, vector<int>(n+1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> A[i][j];
    }
  }

  vector<vector<AdjEntry>> adj(n+1);
  DSU dsu(n+1);

  for (int i = 1; i <= n; i++) {
    for (int j = i+1; j <= n; j++) {
      // Slot A[i][j] is touched by operations i and j
      if (A[i][j] == A[j][i])  continue;  //don't care
      if (dsu.connected(i, j))  continue;  //do nothing if edge is redundant or potentially creates a contradiction. edges are traversed highest prio first

      dsu.unite(i, j);
      if (A[i][j] < A[j][i]) {
        // then we want i and j to be the same, so the current state is kept
        adj[i].pb(AdjEntry{j, false});
        adj[j].pb(AdjEntry{i, false});
      } else {
        // then we want i and j to be different, so we flip and have smaller one here
        adj[i].pb(AdjEntry{j, true});
        adj[j].pb(AdjEntry{i, true});
      }
    }
  }

  vector<bool> visited(n+1, false);
  vector<bool> settings(n+1, false);

  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      // initial state is arbitrary
      dfs(i, adj, visited, settings);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i+1; j <= n; j++) {
      if (settings[i] ^ settings[j]) {
        swap(A[i][j], A[j][i]);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << A[i][j] << " ";
    }
    cout << "\n";
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
