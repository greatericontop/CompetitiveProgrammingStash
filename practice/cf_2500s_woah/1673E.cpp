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








int calc_signed_choose(int n, int k) {
  // where to start
  if (k < 0)  k = 0;
  if (n == 0 && k == 0)  return 1;
  if (n == 0 && k > 0)  return 0;

  int accumulator = 0;
  int powerof2ct = 0;
  for (int i = 0; i <= n; i++) {
    if (i > 0) {
      // multiply by n-i+1
      powerof2ct += __builtin_ctz(n-i+1);
      // divide by i
      powerof2ct -= __builtin_ctz(i);
      assert(powerof2ct >= 0);
    }

    if (i >= k) {
      if (powerof2ct > 0) {
        // number is currently even
      } else {
        // number is currently odd
        accumulator += 1;
      }
    }
  }
  assert(powerof2ct == 0);  //should have ended at 1

  accumulator %= 2;
  return accumulator;
}


void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> b(n);
  FORI(n)  cin >> b[i];

  // bruh u suck at cp
  // the max length is 20 (2^1 from the first, then 2^2, 2^4, etc.)
  vector<int> answers(22);  //place k-2
  vector<int> answers_border(22);  //place k-1
  for (int sz = 1; sz < 22; sz++) {
    answers[sz] = calc_signed_choose(n-2-sz, k-2);
    answers_border[sz] = calc_signed_choose(n-1-sz, k-1);
  }

  string ret(1048576, '0');
  for (int i = 0; i < n; i++) {  //array starts at i
    long this_subarray = b[i];
    for (int j = i; j < n; j++) {  //array ends at j (inclusive)
      if (j != i) {
        if (b[j] >= 20)  break;
        this_subarray *= (1LL << b[j]);
        if (this_subarray >= 1048576)  break;
      }

      int multiplier;
      if (i == 0 && j == n-1) {
        // special case: 1 if 0 dividers is allowed
        multiplier = (k == 0) ? 1 : 0;
      } else if (i == 0 || j == n-1) {
        multiplier = answers_border[j-i+1];
      } else {
        multiplier = answers[j-i+1];
      }

      if (multiplier == 1) {
        fprintf(stderr, "multiplier = 1 for subarray %d %d (size=%d)\n", i, j, j-i+1);
        ret[this_subarray] = (ret[this_subarray] == '0' ? '1' : '0');
      }
    }
  }

  bool seen_first_one = false;
  string output;
  for (int i = 1048575; i >= 0; i--) {
    char c = ret[i];
    if (c == '1')  seen_first_one = true;
    if (seen_first_one)  output += c;
  }
  if (!seen_first_one)  output = "0";
  cout << output << "\n";
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
