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







#define MAXSTATE 100'000


void solve(const vector<vector<int>>& factors, const vector<vector<int>>& prime_factors) {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<int> freq(100'001);
  for (int x : a)  freq[x]++;

  vector<long> state(MAXSTATE+1, 0);
  long ans = 0;
  int i = n;
  for (int x = MAXSTATE; x >= 1; x--) {
    int ct = freq[x];
    if (ct == 0)  continue;

    fprintf(stderr, "before x=%d x%d  ", x, ct);  PRINTVEC(state);
    // this number -> other numbers
    long total = 0;
    for (int g : factors[x]) {
      long there = 0;
      fprintf(stderr, "PIE g=%d  ", g);
      // gcd of g
      int extra = x / g;
      const vector<int>& extra_primes = prime_factors[extra];
      // count using PIE
      for (int mask = 0; mask < (1 << extra_primes.size()); mask++) {
        int prod = 1;
        int bits = 0;
        for (int j = 0; j < extra_primes.size(); j++) {
          if (mask & (1 << j)) {
            prod *= extra_primes[j];
            bits++;
          }
        }
        long sign = (bits % 2 == 0) ? 1 : -1;
        there += sign * state[g * prod];
      }
      fprintf(stderr, "  there %ld * %d\n", there, g);
      total += there * g;
    }
    fprintf(stderr, "PIE total = %ld\n", total);
    ans += LONG(ct) * total;

    // this number to itself & update state
    long add_this_much = 0;
    for (int z = 0; z < ct; z++) {
      fprintf(stderr, "z = %d, i = %d\n", z, i);
      ans += add_this_much * x;
      fprintf(stderr, "ans += %ld\n", add_this_much*x);
      add_this_much += (n-i);
      i--;
    }

    for (int g : factors[x]) {
      state[g] += add_this_much;
    }
  }

  cout << ans << "\n";
}









/*
 * Linear Sieve of Eratosthenes
 * Saves the results in :primes: and :spf:
 */
void linear_sieve(int n, vector<int>& primes, vector<int>& spf) {
  primes.clear();
  for (int i = 0; i < spf.size(); i++) {
    spf[i] = i;
  }

  for (int i = 2; i <= n; i++) {
    if (spf[i] == i) {
      primes.push_back(i);
    }

    for (int prime : primes) {
      if (prime > spf[i])  break;
      int composite_number = prime * i;
      if (composite_number > n)  break;
      spf[composite_number] = prime;
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> primes;
  vector<int> spf(100'020);
  linear_sieve(100'010, primes, spf);

  vector<vector<int>> prime_factors(100'001);
  for (int x = 2; x <= 100'000; x++) {
    set<int> f;
    int y = x;
    while (y > 1) {
      f.insert(spf[y]);
      y /= spf[y];
    }
    prime_factors[x] = vector<int>(f.begin(), f.end());
  }
  vector<vector<int>> factors(100'001);
  for (int x = 1; x <= 100'000; x++) {
    for (int y = x; y <= 100'000; y += x) {
      factors[y].pb(x);
    }
  }

  int t = 1;
  cin >> t;
  while (t--)  solve(factors, prime_factors);
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
