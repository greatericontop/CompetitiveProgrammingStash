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






constexpr inline long rangesum(long a, long b) {
  return (a + b) * (b - a + 1) / 2;
}




void solve() {
  int n, q;
  cin >> n >> q;
  vector<long> a(n);
  FORI(n)  cin >> a[i];
  sort(a.begin(), a.end());
  vector<long> modded(n);
  FORI(n)  modded[i] = a[i] - i;
  vector<long> modded_prefix_min(n);
  modded_prefix_min[0] = modded[0];
  for (int i = 1; i < n; i++)  modded_prefix_min[i] = min(modded_prefix_min[i-1], modded[i]);
  long a_sum = accumulate(a.begin(), a.end(), 0LL);

  while (q --> 0) {
    long k;  cin >> k;
    if (k <= n) {
      long suffix_section = k == n ? LONG(1e18) : a[k];
      long prefix_section = modded_prefix_min[k-1] + k;  //a[0] is increased by k, a[1] by k-1, etc
      cout << min(suffix_section, prefix_section) << " ";
    } else if ((k-n) % 2 == 0) {
      // What we can achieve, bottlenecked by min elt
      long possible_minimum = modded_prefix_min[n-1] + k;
      // What we can achieve, bottlenecked by sum
      long penalty_terms = (k - n) / 2;  //-1 each
      long new_a_sum = a_sum - penalty_terms + rangesum(k-n+1, k);
      assert(new_a_sum >= 0);  //a single +k should dwarf the penalty terms
      long possible_minimum2 = new_a_sum / n;
      cout << min(possible_minimum, possible_minimum2) << " ";
    } else {  //odd
      if (n == 1) {
        assert(k % 2 == 0);
        a[0] -= k/2;
        cout << a[0] << " ";
      } else {
        long possible_minimum = min(modded_prefix_min[n-2] + k, a[n-1]);
        long penalty_terms = (k - (n-1)) / 2;
        long new_a_sum = a_sum - penalty_terms + rangesum(k-n+2, k);
        assert(new_a_sum >= 0);
        long possible_minimum2 = new_a_sum / n;
        cout << min(possible_minimum, possible_minimum2) << " ";
      }
    }
  }
  cout << "\n";

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
