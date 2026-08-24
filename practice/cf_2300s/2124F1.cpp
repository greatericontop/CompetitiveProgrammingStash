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










void solve() {
  int n, m;
  cin >> n >> m;
  bool legal[n+1][n+1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      legal[i][j] = true;
    }
  }
  FORI(m) {
    int a, b;  cin >> a >> b;
    legal[a][b] = false;
  }
  long dp[n+1][n+1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = 0;
    }
  }

  dp[0][0] = 1;  //dp[i=0][0 means unrestricted]
  int b[n];  //in practice b[s]
  for (int i = 0; i < n; i++) {
    long dpi_sum = 0;
    for (int j = 0; j <= n; j++)  dpi_sum += dp[i][j];
    for (int s = 1; s <= n-i; s++) {
      // dp[i] ---> dp[i+s]
      for (int shiftquan = 0; shiftquan < s; shiftquan++) {
        for (int j = 0; j < s; j++) {
          b[j] = ((j + shiftquan) % s) + 1;
        }
        bool islegal = true;
        for (int j = 0; j < s; j++) {
          // check if b[j] is a valid number for position i+j+1
          if (!legal[i+j+1][b[j]]) {
            islegal = false;
            break;
          }
        }
        if (islegal) {
          // Calculate how many combos in dp[i] are valid for transition
          long validcombos = dpi_sum;
          if (b[0] != 1) {
            // ex. if b is [2 3 1], then can't transition from dp[i][1]
            validcombos -= dp[i][b[0]-1];
          }
          // Now add them
          if (b[0] == 1) {
            assert(b[s-1] == s);
            dp[i+s][s] += validcombos;
            dp[i+s][s] %= MOD;
          } else {
            dp[i+s][0] += validcombos;
            dp[i+s][0] %= MOD;
          }
        }
      }
    }
  }

  long ans = 0;
  for (int j = 0; j <= n; j++) {
    ans += dp[n][j];
    ans %= MOD;
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
