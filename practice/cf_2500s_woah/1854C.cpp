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

/* n may be reduced % MOD, but not k, O(k) */
int64_t choose_mod(int64_t n, int64_t k) {
  if (k > n)  return 0;
  int64_t top = 1; // n * ... * (n - k + 1)
  int64_t bottom = 1; // k!
  for (int64_t i = 1; i <= k; i++) {
    top = (top * ((n - i + 1) % MOD)) % MOD;
    bottom = (bottom * i) % MOD;
  }
  return (top * modular_inverse(bottom)) % MOD;
}









void solve() {
  long FACTORIALS[2001];
  FACTORIALS[0] = 1;
  for (int i = 1; i <= 2000; i++) {
    FACTORIALS[i] = (FACTORIALS[i - 1] * i) % MOD;
  }
  long FACTORIALS_INV[2001];
  for (int i = 0; i <= 2000; i++) {
    FACTORIALS_INV[i] = modular_inverse(FACTORIALS[i]);
  }
  auto choose = [&](int n, int k) {
    assert(k >= 0 && k <= n);
    return (((FACTORIALS[n] * FACTORIALS_INV[k]) % MOD) * FACTORIALS_INV[n - k]) % MOD;
  };


  vector<vector<long>> dp_count(501, vector<long>(501, -1));
  vector<vector<long>> dp_frac(501, vector<long>(501, -1));

  for (int x = 1; x <= 500; x++) {
    for (int y = x; y <= 500; y++) {
      long denominator = mod_exp(2, 2*y-x);

      long basic = choose(2*y-x, y);
      for (int minus = 1; y-minus >= x; minus++) {
        long to_subtract = (dp_count[x][y-minus] * choose(2*minus, minus)) % MOD;
        basic = (basic - to_subtract + MOD) % MOD;
      }

      dp_count[x][y] = basic;
      dp_frac[x][y] = (basic * modular_inverse(denominator)) % MOD;
    }
  }

  for (int x = 1; x <= 3; x++) {
    for (int y = x; y <= 3; y++) {
      fprintf(stderr, "dp_count[x=%d][y=%d] = %ld\n", x, y, dp_count[x][y]);
    }
  }

  int n, m;
  cin >> n >> m;
  vector<int> S(n);
  FORI(n)  cin >> S[i];

  int default_timecost = 0;
  for (int x : S)  default_timecost += m + 1 - x;
  fprintf(stderr, "default timecost %d\n", default_timecost);

  long ans = default_timecost;
  for (int i = 0; i < n-1; i++) {
    int x1 = S[i], x2 = S[i+1];
    for (int meetup_time = x2; meetup_time <= m; meetup_time++) {
      int saved_time = m + 1 - meetup_time;
      fprintf(stderr, "  x1=%d, x2=%d, meetup at %d, saves time %d, dp[%d][%d]=(x%ld)\n", x1, x2, meetup_time, saved_time, x2-x1, meetup_time-x1, dp_count[x2-x1][meetup_time-x1]);
      long odds = dp_frac[x2-x1][meetup_time-x1];
      long expected_saved_time = (odds * saved_time) % MOD;
      ans = (ans - expected_saved_time + MOD) % MOD;
    }
  }

  cout << ans << "\n";

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
