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










void solve(const vector<long>& totient_prefix_sum) {
  int n, m;  cin >> n >> m;

  long sum_possible = 0;
  long m_left = m;
  long ops = 0;
  bool didbreak = false;
  for (int w = n; w >= 2; w--) {
    // Add edges of weight w
    int k = w-1;  //number of edges per bundle
    long edges_avail = totient_prefix_sum[n/w];
    fprintf(stderr, "w=%d, n/w=%d, edges avail %ld\n", w, n/w, edges_avail);
    long bundles_avail = edges_avail / k;
    fprintf(stderr, "  %ld bundles of %d\n", bundles_avail, k);

    sum_possible += k * bundles_avail;
    if (k * bundles_avail >= m_left) {
      // use as many as we can, leaving behind a remainder that is less than w. (will handle the remainder 1 case specially)
      long bundles_used = m_left / k;
      ops += bundles_used;
      m_left -= k * bundles_used;
      didbreak = true;
      break;
    } else {
      // use them all
      ops += bundles_avail;
      m_left -= k * bundles_avail;
    }
  }

  if (!didbreak) {
    // not enough
    assert(m > sum_possible);
    cout << -1 << "\n";
    return;
  }

  if (m == sum_possible-1) {
    assert(m_left == 1);
    cout << -1 << "\n";
  } else {
    long ans = m + ops + (m_left == 0 ? 0 : 1);
    cout << ans << "\n";
  }
}






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
  vector<int> spf(1'000'020);
  linear_sieve(1'000'010, primes, spf);
  vector<int> totients(1'000'010);
  for (int i = 2; i <= 1'000'010; i++) {
    int x = i;
    int tot = 1;
    while (x > 1) {
      int p = spf[x];
      while (x % p == 0) {
        x /= p;
        tot *= p;
      }
      tot = tot / p * (p - 1);
    }
    totients[i] = tot;
  }
  vector<long> totient_prefix_sum(1'000'010, 0);
  for (int i = 2; i <= 1'000'010; i++) {
    totient_prefix_sum[i] = totient_prefix_sum[i-1] + totients[i];
  }

  int t = 1;
  cin >> t;
  while (t--)  solve(totient_prefix_sum);
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
