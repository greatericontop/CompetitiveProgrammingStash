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
/* O(log exp) */
int64_t mod_exp(int64_t base, int64_t exp, int64_t MOD) {
  int64_t result = 1;
  while (exp > 0) {
    if (exp & 1)  result = (result * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

/* Only works for primes, O(log MOD) */
int64_t modular_inverse(int64_t a, int64_t MOD) {
  return mod_exp(a, MOD - 2, MOD);
}










void solve() {
  int n;  long MOD;
  cin >> n >> MOD;

  vector<long> factorials(n+1, 1);
  for (int i = 2; i <= n; i++) {
    factorials[i] = (factorials[i-1] * LONG(i)) % MOD;
  }
  auto fast_choose = [&](long n, long k) -> long {
    //assert(k >= 0 && k <= n);
    return (factorials[n] * modular_inverse((factorials[k] * factorials[n-k]) % MOD, MOD)) % MOD;
  };
  vector<long> precomputed_inverses(n+1, -1);
  for (int x = 0; x <= n; x++) {
    precomputed_inverses[x] = modular_inverse(x, MOD);
  }

  int odd_correction = (n % 2 == 1 ? 1 : 0);
  long total = 0;
  // m: size of the final window, e.g. 3 for 5, and 3 for 6
  for (int m = 1; m <= ceildiv(n, 2); m++) {
    long choose = 1;

    // k: number of points occupying it
    for (int k = 1; k <= m; k++) {
      long ways_to_choose_subset;
      if (k == 1) {
        if (m != 1)  continue;  //can't pick 1 from a window of >=2
        ways_to_choose_subset = n;
      } else {
        // m-2 choose k-2
        ways_to_choose_subset = n * choose;
        ways_to_choose_subset %= MOD;
        // now for k=2 we need to multiply by m-2 and divide by 1
        choose *= m - k;
        choose %= MOD;
        choose *= precomputed_inverses[k-1];
        choose %= MOD;
      }

      long ways_to_choose_a = factorials[n-k-1] * LONG(m - odd_correction);
      ways_to_choose_a %= MOD;

      total += (ways_to_choose_subset * ways_to_choose_a);
      total %= MOD;
      fprintf(stderr, "%d from %d, subset %ld, a %ld\n", k, m, ways_to_choose_subset, ways_to_choose_a);
    }
  }

  cout << total << "\n";


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
