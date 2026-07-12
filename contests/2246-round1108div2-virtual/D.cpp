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
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










void solve() {
  int n;
  cin >> n;
  vector<int> a_orig(n);
  FORI(n)  cin >> a_orig[i];

//  int logn = 0;
//  while ((1 << logn) < n+2)  logn++;
//  assert(logn <= 20);

  long best = LONG(1e18);
  for (int e = 0; e <= 20; e++) {
    int twotoe = (1 << e);  //also the cost multiplier
    long roundup_cost = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      int ai_new = ((a_orig[i] + twotoe - 1) / twotoe) * twotoe;
      assert(ai_new - a_orig[i] >= 0 && ai_new - a_orig[i] < twotoe);
      assert(ai_new % twotoe == 0);
      if (e == 0)  assert(ai_new == a_orig[i]);
      a[i] = ai_new / twotoe;
      roundup_cost += LONG(ai_new - a_orig[i]);
    }
    fprintf(stderr, "for 2^%d, ", e); //PRINTVEC(a);

    long turn_costs = 0;
    for (int i = 0; i < n; i++) {
      // try rounding up to each bit position.
      long mincosthere = LONG(1e18);
      for (int b = 0; b <= 20; b++) {
        int twotob = (1 << b);
        int ai_new = ((a[i] + twotob - 1) / twotob) * twotob;
        long costhere = LONG(ai_new - a[i]) * LONG(twotoe);  //cost to increment, plus 2^e multiplier
        // then number of turns is
        int index_of_highest_set_bit = 31 - __builtin_clz((uint32_t)ai_new);  //zerobased since we also count popcount
        int popcount = __builtin_popcount((uint32_t)ai_new);
        mincosthere = min(mincosthere, costhere + index_of_highest_set_bit + popcount);
      }
      assert(mincosthere != LONG(1e18));
      turn_costs += mincosthere;
    }

    long total_turns_here = turn_costs + roundup_cost + e;
    fprintf(stderr, "for 2^%d, turn_costs = %ld, roundup_cost = %ld (total = %ld)\n", e, turn_costs, roundup_cost, total_turns_here);
    best = min(best, total_turns_here);
  }

  assert(best != LONG(1e18));
  cout << best << "\n";

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
