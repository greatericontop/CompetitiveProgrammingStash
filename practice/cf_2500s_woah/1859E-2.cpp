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
//constexpr static long MOD =   998'244'353LL;









constexpr long NEGINF = -1e17;

void solve() {
  int n, kk;
  cin >> n >> kk;
  vector<long> a(n);
  FORI(n)  cin >> a[i];
  vector<long> b(n);
  FORI(n)  cin >> b[i];


  vector<vector<long>> dp(kk+1, vector<long>(n+1, NEGINF));
  vector<vector<long>> prefixplusplus(kk+1, vector<long>(n+1, NEGINF));
  vector<vector<long>> prefixplusminus(kk+1, vector<long>(n+1, NEGINF));
  vector<vector<long>> prefixminusplus(kk+1, vector<long>(n+1, NEGINF));
  vector<vector<long>> prefixminusminus(kk+1, vector<long>(n+1, NEGINF));

  auto update_pref = [&](int l, int i) {
    if (i == 0)  return;  //we will never read this anyway
    long aval = a[i-1], bval = b[i-1];
    if (l > 0 && i < n) {
      prefixplusplus[l][i] = prefixplusplus[l-1][i+1];
      prefixplusminus[l][i] = prefixplusminus[l-1][i+1];
      prefixminusplus[l][i] = prefixminusplus[l-1][i+1];
      prefixminusminus[l][i] = prefixminusminus[l-1][i+1];
    }  //otherwise it stays at -inf
    prefixplusplus[l][i] = max(prefixplusplus[l][i], aval + bval + dp[l][i]);
    prefixplusminus[l][i] = max(prefixplusminus[l][i], aval - bval + dp[l][i]);
    prefixminusplus[l][i] = max(prefixminusplus[l][i], -aval + bval + dp[l][i]);
    prefixminusminus[l][i] = max(prefixminusminus[l][i], -aval - bval + dp[l][i]);
  };

  {
    for (int i = n; i >= 0; i--) {
      dp[0][i] = 0;  //zero distance left
      update_pref(0, i);
    }
  }
  for (int l = 1; l <= kk; l++) {
    // dp[l >= 1][n] = NEGINF since need exact amount
    for (int i = n-1; i >= 0; i--) {
      long v = dp[l][i+1];

      long x = b[i], y = a[i];
      // prefix entries start at l-1, i+1
      v = max(v, prefixplusplus[l-1][i+1] - x - y);
      v = max(v, prefixplusminus[l-1][i+1] - x + y);
      v = max(v, prefixminusplus[l-1][i+1] + x - y);
      v = max(v, prefixminusminus[l-1][i+1] + x + y);

      dp[l][i] = v;
      update_pref(l, i);
    }
  }

  long ans = dp[kk][0];
  assert(ans > NEGINF);
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
