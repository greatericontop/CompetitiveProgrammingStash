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










vector<vector<long>> setup(int k) {
  vector<long> factorials(k+1, 1);
  for (int i = 1; i <= k; i++) {
    factorials[i] = (factorials[i-1] * LONG(i)) % MOD;
  }
  auto choose = [&](int n, int r) -> long {
    assert(n >= 0 && r >= 0 && n >= r);
    long top = factorials[n];
    long bottom = (factorials[r] * factorials[n-r]) % MOD;
    return (top * modular_inverse(bottom)) % MOD;
  };

  vector<vector<long>> data(k+1, vector<long>(k+1, 0));
  vector<vector<long>> prefix_sum(k+1, vector<long>(k+1, 0));
  for (int tot = 1; tot <= k; tot++) {
    for (int unique = 1; unique <= tot; unique++) {
      // how many ways are there to fill unique out of tot?
      if (unique == 1) {
        // if only 1 unique, then tot ways (all are the same, tot different choices)
        data[tot][unique] = tot;
      } else {
        long ways_to_pick_unique = choose(tot, unique);
        // for each subset, :unique: choices each, pick k elements
        long per_subset = mod_exp(unique, k);
        // subtract out 1/unique, 2/unique, ..., (unique-1)/unique
        long subtract = prefix_sum[unique][unique-1];
        per_subset = (per_subset - subtract + MOD) % MOD;
        data[tot][unique] = (ways_to_pick_unique * per_subset) % MOD;
      }
      // Update: prefix_sum[tot][x] stores prefix_sum[tot][1 + ... + x unique]
      prefix_sum[tot][unique] = (prefix_sum[tot][unique-1] + data[tot][unique]) % MOD;
    }
  }

  return data;
}


void solve(vector<vector<long>>& data) {
  long n, m;  int k;
  cin >> n >> m >> k;

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<vector<long>> data = setup(2000);
  int t = 1;
  cin >> t;
  while (t--)  solve(data);
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
