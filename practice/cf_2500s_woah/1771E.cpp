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










void solve() {
  int n, m;  cin >> n >> m;
  vector<string> a(n);
  FORI(n)  cin >> a[i];

  for (int c1 = 0; c1 < m; c1++) {
    for (int c2 = c1+1; c2 < m; c2++) {  // 400^2/2
      string column_merge(n, '_');
      for (int i = 0; i < n; i++) {
        if (a[i][c1] == '#' || a[i][c2] == '#' || (a[i][c1] == 'm' && a[i][c2] == 'm'))  column_merge[i] = '#';
        else if (a[i][c1] == 'm' || a[i][c2] == 'm')  column_merge[i] = 'm';
        else  column_merge[i] = '.';
      }

      vector<int> largest_perfect(n, -1);
      int last_block = -1;  //so 0 can be covered
      for (int i = 0; i <= n; i++) {
        if (i == n || column_merge[i] == '#' || column_merge[i] == 'm') {
          int size = i - last_block - 1;
          for (int t = last_block + 1; t < i; t++) {
            largest_perfect[t] = size;
          }
          if (i < n)  largest_perfect[i] = 0;
          last_block = i;
        }
      }

      vector<int> left_m(n, -1);
      last_block = -1;
      for (int i = 0; i < n; i++) {
        if (column_merge[i] == 'm')  last_block = i;
        if (column_merge[i] == '#')  last_block = -1;
        left_m[i] = last_block;
      }
      vector<int> right_m(n, -1);
      last_block = -1;
      for (int i = n-1; i >= 0; i--) {
        if (column_merge[i] == 'm')  last_block = i;
        if (column_merge[i] == '#')  last_block = -1;
        right_m[i] = last_block;
      }

      vector<int> largest_imperfect(n, -1);
      for (int i = 0; i < n; i++) {
        if (column_merge[i] == '#') {
          largest_imperfect[i] = 0;
        } else if (column_merge[i] == 'm') {
          int x = 0;
          if (i > 0)  x += largest_perfect[i-1];
          if (i < n-1)  x += largest_perfect[i+1];
          largest_imperfect[i] = x;
        } else {
          int here = largest_perfect[i];
          int best = here;
          if (left_m[i] != -1) {
            int x = here + 1;
            if (left_m[i] > 0)  x += largest_perfect[left_m[i]-1];
            best = max(best, x);
          }
          if (right_m[i] != -1) {
            int x = here + 1;
            if (right_m[i] < n-1)  x += largest_perfect[right_m[i]+1];
            best = max(best, x);
          }
          largest_imperfect[i] = best;
        }
      }

      for (int row = 1; row < n; row++) {

      }

    }
  }

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
