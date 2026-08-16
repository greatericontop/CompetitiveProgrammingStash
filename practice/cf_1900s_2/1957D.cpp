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
//constexpr static long MOD =   998'244'353LL;









// b must be 0-1
long solve_basic(int n, const vector<int>& b, const vector<int>& msbs, int which_msb) {
  vector<int> left_odd(n), left_even(n);
  int odd = 0, even = 0;
  bool cur = true;  //true if currently even
  for (int i = 0; i < n; i++) {
    if (cur)  even++;  else  odd++;
    left_odd[i] = odd;
    left_even[i] = even;
    if (b[i] == 1) {
      cur = !cur;
    }
  }
  bool total_parity = cur;  // if overall count is even (cur is true), then want to cut out even
  vector<int> right_odd(n), right_even(n);
  odd = 0, even = 0;
  cur = true;
  for (int i = n-1; i >= 0; i--) {
    if (cur)  even++;  else  odd++;
    right_odd[i] = odd;
    right_even[i] = even;
    if (b[i] == 1) {
      cur = !cur;
    }
  }

  long tot = 0;
  for (int i = 0; i < n; i++) {
    if (msbs[i] != which_msb)  continue;
    assert(b[i] == 1);
    if (total_parity) {
      tot += LONG(left_even[i]) * LONG(right_even[i]);
      tot += LONG(left_odd[i]) * LONG(right_odd[i]);
    } else {
      tot += LONG(left_even[i]) * LONG(right_odd[i]);
      tot += LONG(left_odd[i]) * LONG(right_even[i]);
    }
  }
  return tot;
}



void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  vector<int> msbs(n);
  FORI(n)  msbs[i] = 31 - __builtin_clz(a[i]);

  long tot = 0;
  for (int msb = 29; msb >= 0; msb--) {
    vector<int> b(n);
    FORI(n)  b[i] = (a[i] >> msb) & 1;
    tot += solve_basic(n, b, msbs, msb);
  }

  cout << tot << "\n";


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
