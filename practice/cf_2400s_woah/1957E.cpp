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
constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;






long answers[1'000'010];



struct Lazy {
  long sum;
  vector<long> data;

  void update(int i, long x) {
    assert(sum >= 0 && x >= 0);
    sum += x - data[i];
    sum += MOD;
    sum %= MOD;
    data[i] = x % MOD;
  }
};



void solve() {
  int n;
  cin >> n;
  cout << answers[n] << "\n";
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
void solvereal() {
  int nmax = 1'000'000;
  vector<int> primes;
  vector<int> spf(nmax+1);
  linear_sieve(nmax, primes, spf);
  vector<int> kminus1factorial_mod_k(nmax+1);
  for (int k = 2; k <= nmax; k++) {
    if (k == 4) {
      kminus1factorial_mod_k[k] = 2;
    } else if (spf[k] == k) {
      kminus1factorial_mod_k[k] = k - 1;
    } else {
      kminus1factorial_mod_k[k] = 0;
    }
  }
  vector<vector<int>> poi(nmax+1);
  for (int k = 2; k <= nmax; k++) {
    for (int n = k; n <= nmax; n += k) {
      poi[n].pb(k);
    }
  }

  Lazy lazy = {0, vector<long>(nmax+1, 0)};
  long answer = 0;
  answers[1] = 0;
  for (int n = 2; n <= nmax; n++) {
    // update poi
    for (int k : poi[n]) {
      int multiplier = n / k;
      long contri = (LONG(kminus1factorial_mod_k[k]) * multiplier) % k;
      lazy.update(k, contri);
    }

    answer += lazy.sum;
    answer %= MOD;
    answers[n] = answer;
  }
}






int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solvereal();
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
