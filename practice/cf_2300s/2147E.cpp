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





#define exp(x) (1LL << (x))
/* Force setting bits 0 through msbpos (msbpos+1 total bits) */
long costof(int n, const vector<int>& a, int msbpos) {
  long c = 0;
  vector<int> b = a;

  for (int bit = msbpos; bit >= 0; bit--) {
    FORI(n)  b[i] = b[i] & (exp(bit + 1) - 1);

    bool set = false;  int maxi = -1, maxi_i = -1;
    FORI(n) {
      assert(b[i] < exp(bit + 1));
      if (b[i] & exp(bit)) {
        set = true;
      } else {
        assert(b[i] < exp(bit));
        if (b[i] > maxi) {
          maxi = b[i];
          maxi_i = i;
        }
      }
    }
    if (!set) {
      c += exp(bit) - maxi;
      b[maxi_i] = 0;
    }
  }

  assert(c >= 0);
  return c;
}





void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  int a_or = 0;
  FORI(n)  a_or |= a[i];

  vector<long> popcnt_to_cost(32, LONG(1e18));
  for (int i = 0; i <= __builtin_popcount(a_or); i++) {
    popcnt_to_cost[i] = 0;  //already free
  }
  for (int msbpos = 30; msbpos >= 0; msbpos--) {
    // extra bits above msbpos
    int popcount_extra = __builtin_popcount(a_or >> (msbpos+1));
    int popcount = popcount_extra + (msbpos + 1);
    popcnt_to_cost[popcount] = min(popcnt_to_cost[popcount], costof(n, a, msbpos));
  }
  PRINTVECL(popcnt_to_cost);

  while (q --> 0) {
    int k;  cin >> k;

    int max_popcnt = 0;
    for (int p = 0; p < 32; p++) {
      if (popcnt_to_cost[p] <= k) {
        max_popcnt = p;
      }
    }
    cout << max_popcnt << "\n";
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
