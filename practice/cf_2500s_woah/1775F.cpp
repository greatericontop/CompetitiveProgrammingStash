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










void solve_constructive() {
  int n;
  cin >> n;

  int x = 1, y = 1;
  while (true) {
    if (x*y >= n) {
      break;
    }
    if (x == y)  x++;
    else  y++;
  }
  cout << x << " " << y << "\n";
  for (int i = 0; i < x; i++) {
    string s(y, '#');
    for (int j = 0; j < y; j++) {
      int idx = i*y + j;
      if (idx >= n)  s[j] = '.';
    }
    cout << s << "\n";
  }
}


void solve_counting(int t) {
  int mod;  cin >> mod;
  // Precompute all answers
  vector<vector<long>> dp(651, vector<long>(651, 0));
  for (int j = 0; j <= 650; j++)  dp[0][j] = 1;
  for (int i = 1; i <= 650; i++) {
    dp[i][0] = 0;
    for (int m = 1; m <= i; m++) {
      dp[i][m] = dp[i][m-1] + dp[i-m][m];
      if (dp[i][m] >= mod)  dp[i][m] -= mod;
    }
    for (int m = i+1; m <= 650; m++) {
      dp[i][m] = dp[i][m-1];
    }
  }
  vector<long> dp1(651);
  for (int i = 0; i <= 650; i++)  dp1[i] = dp[i][i];
  //PRINTVECL(dp1);
  vector<long> dp2(651);
  for (int i = 0; i <= 650; i++) {
    dp2[i] = 0;
    for (int j = 0; j <= i; j++) {
      dp2[i] += dp1[j] * dp1[i-j];
      dp2[i] %= mod;
    }
  }
  vector<long> dp4(651);
  for (int i = 0; i <= 650; i++) {
    dp4[i] = 0;
    for (int j = 0; j <= i; j++) {
      dp4[i] += dp2[j] * dp2[i-j];
      dp4[i] %= mod;
    }
  }
  PRINTVECL(dp4);

  vector<pairii> answers(400001);
  int xbest = 1, ybest = 1;
  for (int n = 1; n <= 400000; n++) {
    if (xbest * ybest < n) {
      if (xbest == ybest)  xbest++;  else  ybest++;
      assert(xbest * ybest >= n);
      assert(xbest <= 650 && ybest <= 650);
    }
    int best_perimeter = 2 * (xbest + ybest);
    long ways = 0;
    for (int d = 0; true; d++) {
      int x = xbest + d, y = ybest - d;
      if (y <= 0)  break;
      if (x * y < n)  break;
      int extra = x*y - n;  assert(extra >= 0 && extra < x && extra < y && extra <= 650);
      if (n == 7)  fprintf(stderr, "x=%d, y=%d, extra %d (x%ld)\n", x, y, extra, dp4[extra]);
      ways += (x == y ? 1 : 2) * dp4[extra];
      ways %= mod;
    }
    answers[n] = {best_perimeter, ways};
  }

  while (t --> 0) {
    int n;  cin >> n;
    cout << answers[n].first << " " << answers[n].second << "\n";
  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, which;  cin >> t >> which;
  if (which == 1) {
    while (t --> 0) {
      solve_constructive();
    }
  } else {
    solve_counting(t);
  }
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
