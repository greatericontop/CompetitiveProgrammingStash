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








struct Op {
  int i;
  int j;
};


void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<Op> ans;

  int max_abs = 0, index_of_max_abs = -1;
  int pos_count = 0, neg_count = 0;
  for (int i = 0; i < n; i++) {
    int x = a[i];
    if (abs(x) >= abs(max_abs)) {
      max_abs = x;
      index_of_max_abs = i;
    }
    if (x >= 0)  pos_count++;
    else  neg_count++;
  }


  if (min(pos_count, neg_count) >= 8) {
    // standard solution
    for (int i = 0; i < n; i++) {
      if ((a[i] < 0 && max_abs >= 0) || (a[i] >= 0 && max_abs < 0)) {
        a[i] += max_abs;
        ans.pb({i, index_of_max_abs});
      }
    }
  } else {
    // scuffed solution
    if (pos_count >= neg_count) {
      // find the highest positive element, double it 5 times
      int highest_positive_index = -1, highest_positive_value = -1;
      for (int i = 0; i < n; i++) {
        if (a[i] > highest_positive_value) {
          highest_positive_value = a[i];
          highest_positive_index = i;
        }
      }
      ans.pb({highest_positive_index, highest_positive_index});  a[highest_positive_index] *= 2;
      ans.pb({highest_positive_index, highest_positive_index});  a[highest_positive_index] *= 2;
      ans.pb({highest_positive_index, highest_positive_index});  a[highest_positive_index] *= 2;
      ans.pb({highest_positive_index, highest_positive_index});  a[highest_positive_index] *= 2;
      ans.pb({highest_positive_index, highest_positive_index});  a[highest_positive_index] *= 2;
      for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
          a[i] += a[highest_positive_index];
          ans.pb({i, highest_positive_index});
        }
      }
    } else {
      int highest_neg_index = -1, highest_neg_value = 0;
      for (int i = 0; i < n; i++) {
        if (a[i] < highest_neg_value) {
          highest_neg_value = a[i];
          highest_neg_index = i;
        }
      }
      ans.pb({highest_neg_index, highest_neg_index});  a[highest_neg_index] *= 2;
      ans.pb({highest_neg_index, highest_neg_index});  a[highest_neg_index] *= 2;
      ans.pb({highest_neg_index, highest_neg_index});  a[highest_neg_index] *= 2;
      ans.pb({highest_neg_index, highest_neg_index});  a[highest_neg_index] *= 2;
      ans.pb({highest_neg_index, highest_neg_index});  a[highest_neg_index] *= 2;
      for (int i = 0; i < n; i++) {
        if (a[i] >= 0) {
          a[i] += a[highest_neg_index];
          ans.pb({i, highest_neg_index});
        }
      }
    }
  }


  // finally
  int sum = accumulate(a.begin(), a.end(), 0);
  if (sum >= 0) {
    // positive case
    for (int i = 0; i < n-1; i++) {
      ans.pb({i+1, i});
    }
  } else {
    // negative case
    for (int i = n-1; i > 0; i--) {
      ans.pb({i-1, i});
    }
  }

  cout << ans.size() << "\n";
  for (const auto& op : ans) {
    cout << op.i+1 << " " << op.j+1 << "\n";
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
