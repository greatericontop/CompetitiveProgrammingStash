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
  int n, m;  cin >> n >> m;
  vector<string> a(n+1);
  FORI1(n) {
    cin >> a[i];
    a[i] = '_' + a[i];
  }

  vector<vector<int>> prefix_count_hash(n+1, vector<int>(m+1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      prefix_count_hash[i][j] = (a[i][j] == '#') + prefix_count_hash[i][j-1];
    }
  }
  vector<vector<int>> prefix_count_m(n+1, vector<int>(m+1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      prefix_count_m[i][j] = (a[i][j] == 'm') + prefix_count_m[i][j-1];
    }
  }

  int best = 0;

  for (int c1 = 1; c1 <= m; c1++) {
    for (int c2 = c1+2; c2 <= m; c2++) {  // 400^2/2
      fprintf(stderr, "c1 %d, c2 %d\n", c1, c2);
      string column_merge(n+1, '_');
      vector<int> col_count_m(n+1, 0);
      for (int i = 1; i <= n; i++) {
        if (a[i][c1] == '#' || a[i][c2] == '#' || (a[i][c1] == 'm' && a[i][c2] == 'm'))  column_merge[i] = '#';
        else if (a[i][c1] == 'm' || a[i][c2] == 'm')  column_merge[i] = 'm';
        else  column_merge[i] = '.';
      }
      for (int i = 1; i <= n; i++) {
        col_count_m[i] = (column_merge[i] == 'm') + col_count_m[i-1];
      }
      fprintf(stderr, "  column merge: %s\n", column_merge.c_str());

      vector<int> prefix_count_good_rows(n+1, 0);
      vector<int> prefix_count_imperfect_rows(n+1, 0);
      for (int i = 1; i <= n; i++) {
        // row i spans from c1+1 to c2-1 (prefix sums between c2-1 and c1)
        int ct_hash = prefix_count_hash[i][c2-1] - prefix_count_hash[i][c1];
        int ct_m = prefix_count_m[i][c2-1] - prefix_count_m[i][c1];
        fprintf(stderr, "  row %d: # x%d, m x%d\n", i, ct_hash, ct_m);
        if (ct_hash > 0 || ct_m > 1) {
          prefix_count_good_rows[i] = prefix_count_good_rows[i-1];
          prefix_count_imperfect_rows[i] = prefix_count_imperfect_rows[i-1];
        } else if (ct_m == 1) {
          prefix_count_good_rows[i] = prefix_count_good_rows[i-1];
          prefix_count_imperfect_rows[i] = prefix_count_imperfect_rows[i-1] + 1;
        } else {
          prefix_count_good_rows[i] = prefix_count_good_rows[i-1] + 1;
          prefix_count_imperfect_rows[i] = prefix_count_imperfect_rows[i-1] + 1;
        }
      }

      // no bad chars at all
      int j = 0;  //points to character after i, or points to i if currently invalid
      for (int i = 1; i <= n; i++) {
        if (j < i)  j = i;
        while (j <= n) {
          if (column_merge[j] == 'm' || column_merge[j] == '#')  break;
          j++;
        }
        // window must be at least 3
        if (j-i < 3)  continue;
        // now our column is i to j-1, so valid rows are i+1 to j-2
        int imperfect_rows = prefix_count_imperfect_rows[j-2] - prefix_count_imperfect_rows[i];
        if (imperfect_rows > 0) {
          int score = 2*(j-i) + (c2-c1-1);
          best = max(best, score);
        }
      }
      // one bad char
      j = 0;
      for (int i = 1; i <= n; i++) {
        if (j < i)  j = i;
        while (j <= n) {
          if (column_merge[j] == '#')  break;
          if (column_merge[j] == 'm') {
            // check if i...j is valid
            int m_ct = col_count_m[j] - col_count_m[i-1];
            if (m_ct > 1)  break;
          }
          j++;
        }
        if (j-i < 3)  continue;
        fprintf(stderr, "one m in columns allowed: i=%d expands to j<%d\n", i, j);

        int perfect_rows = prefix_count_good_rows[j-2] - prefix_count_good_rows[i];
        if (perfect_rows > 0) {
          int score = 2*(j-i) + (c2-c1-1);
          best = max(best, score);
          //fprintf(stderr, "perfect row at c1 %");
        }
      }
    }
  }

  cout << best << "\n";

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
 * This code contains the use of comments! You can identify them with the "//" or "/" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
