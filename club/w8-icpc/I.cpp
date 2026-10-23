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
constexpr static long MOD =   998'244'353LL;




// returns -1 if none
long sqrt_exact(long x) {
  long l = 1, r = 2e9;
  while (l < r) {
    long m = l + (r-l)/2;
    if (m*m < x)  l = m+1;
    else  r = m;
  }
  assert(l != 2e9);
  if (l*l == x)  return l;
  else  return -1;
}
long sqrt3_exact(long x) {
  long l = 1, r = 1'500'000;
  while (l < r) {
    long m = l + (r-l)/2;
    if (m*m*m < x)  l = m+1;
    else  r = m;
  }
  assert(l != 1'500'000);
  if (l*l*l == x)  return l;
  else  return -1;
}
long sqrt4_exact(long x) {
  long l = 1, r = 40000;
  while (l < r) {
    long m = l + (r-l)/2;
    if (m*m*m*m < x)  l = m+1;
    else  r = m;
  }
  assert(l != 40000);
  if (l*l*l*l == x)  return l;
  else  return -1;
}




void solve() {
  int n;
  cin >> n;
  map<long, int> a_orig;
  FORI(n) {
    long x;  cin >> x;
    if (x == 1)  continue;
    a_orig[x]++;
  }  //freq table

  map<long, long> product_primefac;
  set<long> primes;
  long extra_primefac = 1;

  map<long, int> a2;
  for (auto [x, ct] : a_orig) {
    long rt4 = sqrt4_exact(x);
    if (rt4 != -1) {
      primes.insert(rt4);
      product_primefac[rt4] += 4 * ct;
      continue;
    }
    long rt3 = sqrt3_exact(x);
    if (rt3 != -1) {
      primes.insert(rt3);
      product_primefac[rt3] += 3 * ct;
      continue;
    }
    long rt = sqrt_exact(x);
    if (rt != -1) {
      primes.insert(rt);
      product_primefac[rt] += 2 * ct;
      continue;
    }
    // otherwise, do nothing
    a2[x] = ct;
  }

  // now extract all primes from pairwise facs
  vector<long> nums;
  for (auto [x, ct] : a2)  nums.pb(x);
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i+1; j < nums.size(); j++) {
      long g = gcd(nums[i], nums[j]);
      if (g != 1) {
        fprintf(stderr, "  g: %ld\n", g);
        primes.insert(g);
      }
    }
  }

  for (auto [x, ct] : a2) {
    // try to factor it
    for (long p : primes) {
      if (x % p == 0) {
        long q = x / p;
        product_primefac[p] += ct;
        product_primefac[q] += ct;
        goto continue2;
      }
    }

    // otherwise, we assume they are new so we multiply by ct+1, ct+1
    extra_primefac *= (ct+1);
    extra_primefac %= MOD;
    extra_primefac *= (ct+1);
    extra_primefac %= MOD;

    continue2:
    ;
  }

  long ans = extra_primefac;
  for (auto [p, ct] : product_primefac) {
    ans *= LONG(ct+1);
    ans %= MOD;
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
