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
constexpr static long MOD =   998'244'353LL;






long solve_case(int maxidx, int n, const vector<int>& a) {
  // remember a[1] means between 1 and 2

  fprintf(stderr, "\nsolve_case(maxidx=%d, n=%d)\n", maxidx, n);

  // verify monotonicity
  for (int i = 2; i <= maxidx-1; i++) {
    if (a[i] < a[i-1])  return 0;
  }
  for (int i = n-2; i >= maxidx; i--) {
    if (a[i] < a[i+1])  return 0;
  }

  fprintf(stderr, "monotonicity check passed\n");

  set<int> unplaced;  for (int i = 1; i < n; i++)  unplaced.insert(i);
  vector<int> placements(n+1, -1);
  for (int i = 1; i <= maxidx-1; i++) {
    // first occurrence of a new prefix max requires placing a[i] at i
    if (i == 1 || a[i] > a[i-1]) {
      if (!unplaced.count(a[i])) {
        // impossible: thrashing
        return 0;
      }
      placements[i] = a[i];
      unplaced.erase(a[i]);
    }
  }
  for (int i = n-1; i >= maxidx; i--) {
    // placing it at i+1 this time
    if (i == n-1 || a[i] > a[i+1]) {
      if (!unplaced.count(a[i]))  return 0;
      placements[i+1] = a[i];
      unplaced.erase(a[i]);
    }
  }

  PRINTVEC(a);
  PRINTVEC(placements);
  PRINTVEC(unplaced);

  long tot = 1;
  int spots_avail = 0;
  int i = maxidx-1, j = maxidx+1;  //first unavailable spots
  for (auto it = unplaced.rbegin(); it != unplaced.rend(); ++it) {
    int x = *it;
    while (i >= 1 && a[i] > x) {
      if (placements[i] == -1)  spots_avail++;
      i--;
    }
    while (j <= n && a[j-1] > x) {
      if (placements[j] == -1)  spots_avail++;
      j++;
    }
    fprintf(stderr, "spots avail for x=%d is %d\n", x, spots_avail);
    tot = (tot * spots_avail) % MOD;
    spots_avail--;
  }

  return tot;
}






void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI1(n-1) {
    cin >> a[i];
  }
  int max_a = *max_element(a.begin(), a.end());
  // try solving for maximum at max_a_idx and max_a_idx+1
  set<int> maxes;

  int max_a_start = -1, max_a_end = -1;
  for (int i = 1; i <= n-1; i++) {
    if (a[i] == max_a) {
      if (max_a_start == -1)  max_a_start = i;
      max_a_end = i;
    }
  }
  maxes.insert(max_a_start);
  maxes.insert(max_a_end+1);

  long ans = 0;
  for (int maxidx : maxes) {
    long res = solve_case(maxidx, n, a);
    fprintf(stderr, "solve_case(maxidx=%d) = %lld\n", maxidx, res);
    ans = (ans + res) % MOD;
  }
  cout << ans << "\n";

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
