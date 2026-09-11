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










void solve() {
  int n;
  cin >> n;
  vector<int> p(n+1), q(n+1), locations_of_p(n+1), locations_of_q(n+1);
  FORI1(n) {
    cin >> p[i];
    locations_of_p[p[i]] = i;
  }
  FORI1(n) {
    cin >> q[i];
    locations_of_q[q[i]] = i;
  }

  long tot = 0;

  {
    // k = 0
    long avoid1 = locations_of_p[1], avoid2 = locations_of_q[1];
    if (avoid1 > avoid2)  swap(avoid1, avoid2);

    long x1 = avoid1-1;
    if (x1 >= 1)  tot += x1*(x1+1)/2;  //ex avoid index 5, so any of 1,2,3,4 is fair game
    long x2 = avoid2-avoid1-1;  //ex avoid 4 and 7, so 5,6 are fair game
    if (x2 >= 1)  tot += x2*(x2+1)/2;
    long x3 = n - avoid2;  //ex avoid 4, n = 5, so 5 is fair game
    if (x3 >= 1)  tot += x3*(x3+1)/2;
  }
  fprintf(stderr, "answer after 0 = %ld\n", tot);


  int left = min(locations_of_p[1], locations_of_q[1]);
  int right = max(locations_of_p[1], locations_of_q[1]);
  // must be <=left and >=right in order to include all first 1...k elts

  for (int k = 1; k < n; k++) {
    fprintf(stderr, "before k=%d, left right %d %d\n", k, left, right);
    int m1 = locations_of_p[k+1], m2 = locations_of_q[k+1];
    int valid_left_idx = max(m1, m2);
    if (valid_left_idx > left)  valid_left_idx = 1;
    int valid_right_idx = min(m1, m2);
    if (valid_right_idx < right)  valid_right_idx = n;

    int valid_left_ct = left - valid_left_idx;
    int valid_right_ct = valid_right_idx - right;
    if (valid_left_ct >= 1 && valid_right_ct >= 1) {
      tot += LONG(valid_left_ct) * LONG(valid_right_ct);
    }

    left = min(left, min(m1, m2));
    right = max(right, max(m1, m2));

    fprintf(stderr, "answer after %d = %ld\n", k, tot);
  }

  tot++;  //k = n

  cout << tot << endl;

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
