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
//#define long int64_t
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


//#define long __int128
#define long int64_t










void solve() {
  int64_t S; int q;
  cin >> S >> q;
  set<long> _factors;
  for (long x = 1; x*x <= S; x++) {
    long y = S/x;
    if (x * y == S) {
      _factors.insert(x);
      _factors.insert(y);
    }
  }
  vector<long> factors;
  vector<long> limits;
  for (long x : _factors) {
    factors.pb(x);
    limits.pb(S/x);
  }
  int Fcount = factors.size();
  PRINTVECL(factors);
  PRINTVECL(limits);

  vector<__int128> psum(Fcount);
  psum[0] = factors[0] * limits[0];
  for (int i = 1; i < Fcount; i++) {
    long here = (factors[i] - factors[i-1]) * limits[i];
    psum[i] = psum[i-1] + here;
  }

  while (q --> 0) {
    int64_t x, y;  cin >> x >> y;
    // we will work with y height as our main coordinate
    // find highest factors where limit >= x
    int l = 0, r = Fcount-1;  //factors[0] = 1 is guaranteed to work
    while (l < r) {
      int m = l + (r-l+1)/2;
      long lim = limits[m];
      if (lim >= x) {
        l = m;
      } else {
        r = m-1;
      }
    }
    long highest_fully_accounted = factors[l];
    if (highest_fully_accounted >= y) {
      cout << (x*y) << "\n";
      continue;
    }
    long tot = highest_fully_accounted * x;
    fprintf(stderr, "highest fully-accounted factor: %ld; current total %ld\n", highest_fully_accounted, tot);

    // First factor that sits above
    auto it = lower_bound(factors.begin(), factors.end(), y);
    assert(it != factors.end());
    int top_idx = it - factors.begin();
    tot += psum[top_idx] - psum[l];  //because we already accounted for l and below
    fprintf(stderr, "increase tot by %ld\n", psum[top_idx] - psum[l]);
    // adjust for wastage
    tot -= (factors[top_idx] - y) * limits[top_idx];

    cout << ((int64_t)tot) << "\n";
  }



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
