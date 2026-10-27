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
  vector<int> p(n+1);
  FORI1(n)  cin >> p[i];

  vector<set<int>> cycles;

  vector<bool> visited(n+1, false);
  for (int i = 1; i <= n; i++) {
    if (visited[i])  continue;
    set<int> this_cyc;
    int cur = i;
    while (true) {
      if (visited[cur])  break;
      this_cyc.insert(cur);
      visited[cur] = true;
      cur = p[cur];
    }
    if (this_cyc.size() > 1) {
      cycles.pb(this_cyc);
    }
  }

  if (cycles.size() == 0) {
    for (int i = 1; i <= n; i++)  assert(p[i] == i);
    long ans = LONG(2*n) * LONG(2*n+1) / 2;
    cout << ans << "\n";
    return;
  }
  long ans = 0;
  bool all_size2 = true;
  set<int> sums;
  int mini = INT_MAX, maxi = INT_MIN;
  for (const auto& cyc : cycles) {
    int sz = cyc.size();
    if (sz != 2) {
      all_size2 = false;
    } else {
      int sum = *cyc.begin() + *cyc.rbegin();
      sums.insert(sum);
    }
    mini = min(mini, *cyc.begin());
    maxi = max(maxi, *cyc.rbegin());
  }
  if (all_size2) {
    if (sums.size() == 1) {
      // singleton
      ans++;
    }
  }
  fprintf(stderr, "singleton: %ld\n", ans);

  // anything that includes n+1
  // left is 1...n+1, right is n+1...2n
  ans += LONG(n+1) * LONG(n);
  ans -= 1;  // remove n+1, n+1
  fprintf(stderr, "including n+1: %ld\n", ans);

  // now work through low section, r must be between maxi+1 and n inclusive
  for (int r = maxi+1; r <= n; r++) {
    fprintf(stderr, "r=%d, +%d\n", r, r-1);
    ans += r-1;  //any l from 1 to r-1
  }
  for (int l = n+2; l <= n+mini; l++) {
    fprintf(stderr, "l=%d, +%d\n", l, 2*n-l+1);
    ans += 2*n - l;  // any r from l+1 to 2n
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
