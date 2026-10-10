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
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










constexpr int INFIN = 1e8;

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> colors(n+1);
  FORI1(n)  cin >> colors[i];
  vector<vector<int>> distances(2*n+1, vector<int>(2*n+1, INFIN));
  for (int i = 1; i <= 2*n; i++)  distances[i][i] = 0;
  FORI(m) {
    int u, v;
    cin >> u >> v;
    if (colors[u] == colors[v]) {
      distances[u][v] = 1;
      distances[v][u] = 1;
      distances[u+n][v+n] = 1;
      distances[v+n][u+n] = 1;
    } else {
      distances[u][v+n] = 1;
      distances[v+n][u] = 1;
      distances[v][u+n] = 1;
      distances[u+n][v] = 1;
    }
  }

  for (int kk = 1; kk <= 2*n; kk++) {
    for (int i = 1; i <= 2*n; i++) {
      for (int j = 1; j <= 2*n; j++) {
        distances[i][j] = min(distances[i][j], distances[i][kk] + distances[kk][j]);  //no overflow
      }
    }
  }

  int best_diameter = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      assert(distances[i][j] == distances[j][i]);
      assert(distances[i][j+n] == distances[i+n][j]);
      assert(distances[i][j] == distances[i+n][j+n]);

      int same_parity_dist = distances[i][j];
      int opp_parity_dist = distances[i][j+n];
      for (int x = 0; x < k; x++) {  //yes, adds unnecessary time, IDC
        if (same_parity_dist < opp_parity_dist)  same_parity_dist++;
        else  opp_parity_dist++;
      }
      int dist = min(same_parity_dist, opp_parity_dist);
      fprintf(stderr, "%d to %d has best dist %d\n", i, j, dist);
      assert(dist != INFIN);  //at least one path should have been traversable
      best_diameter = max(best_diameter, dist);
    }
  }

  cout << best_diameter << "\n";
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
