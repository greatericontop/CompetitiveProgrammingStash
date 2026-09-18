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
long FACTORIALS[1'000'010], FACTORIALS_INV[1'000'010];
void init_fac() {
  FACTORIALS[0] = 1;
  for (int i = 1; i < 1'000'010; i++) {
    FACTORIALS[i] = (FACTORIALS[i - 1] * LONG(i)) % MOD;
  }
  for (int i = 0; i < 1'000'010; i++) {
    FACTORIALS_INV[i] = modular_inverse(FACTORIALS[i]);
  }
  fprintf(stderr, "finished initializing factorials\n");
}
long choose(long n, long k) {
  if (k > n)  return 0;
  return (((FACTORIALS[n] * FACTORIALS_INV[k]) % MOD) * FACTORIALS_INV[n - k]) % MOD;
}
long choose_with_consecutive(long n, long k, long c) {
  assert(c > k-c);
  if (k == n)  return 1;
  long blockat1 = choose(n-c, k-c);
  long blockelsewhere = choose(n-c-1, k-c);
  //fprintf(stderr, "block at 1: %ld, elsewhere: %ld\n", blockat1, blockelsewhere);
  long ans = (blockat1 + LONG(n-c)*blockelsewhere) % MOD;
  return ans;
}









void solve() {
  assert(choose_with_consecutive(3, 2, 2) == 2);
  int n;
  cin >> n;
  for (int k = 1; k <= (n-1)/2; k++) {
    // zero deletions
    long ans = 1;
    for (int window_size = 2*k; window_size < n; window_size += 2*k) {
      fprintf(stderr, "k=%d, window size %d\n", k, window_size);
      // add ways to choose window_size
      ans += choose(n, window_size);
      // subtract consecutive
      ans -= choose_with_consecutive(n, window_size, window_size-k+1);
      fprintf(stderr, "  raw choose %ld, subtract %ld\n", choose(n, window_size), choose_with_consecutive(n, window_size, window_size-k+1));
      ans += MOD;  ans %= MOD;
    }
    cout << ans << " ";
  }
  cout << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init_fac();
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
