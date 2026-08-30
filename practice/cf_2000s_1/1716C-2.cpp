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
  int m;  cin >> m;
  vector<long> atop(m+1), adown(m+1);
  FORI1(m) {
    cin >> atop[i];
    atop[i]++;  //so these are the minimum times you can actually be inside
  }
  atop[1]--;  assert(atop[1] == 0);
  FORI1(m) {
    cin >> adown[i];
    adown[i]++;
  }
  PRINTVECL(atop);
  PRINTVECL(adown);

  vector<long> prefixes(m+1);

  // Top prefixes 1, 3, ...
  {
    vector<long> adjusted_down(m+1), adjusted_up(m+1);
    FORI1(m) {
      // down[1] has 0 extra, down[2] has 1 extra, etc
      adjusted_down[i] = adown[i] + (i-1);
      // up[m] has m extra, up[m-1] has m+1 extra, etc
      adjusted_up[i] = atop[i] + m + (m-i);
    }
    long running_max = 0;
    for (int i = m; i >= 1; i--) {
      running_max = max(running_max, max(adjusted_down[i], adjusted_up[i]));
      if (i % 2 == 1) {
        // because adown[i] has +i-1 offset when it should be zero
        long adj = i-1;
        prefixes[i] = running_max - adj;
      }
    }
  }
  {
    vector<long> adjusted_down(m+1), adjusted_up(m+1);
    FORI1(m) {
      adjusted_down[i] = adown[i] + m + (m-i);
      adjusted_up[i] = atop[i] + (i-1);
    }
    long running_max = 0;
    for (int i = m; i >= 1; i--) {
      running_max = max(running_max, max(adjusted_down[i], adjusted_up[i]));
      if (i % 2 == 0) {
        long adj = i-1;
        prefixes[i] = running_max - adj;
      }
    }
  }

  PRINTVECL(prefixes);


  // Answers
  long best = LONG(1e18);
  long running = 0;
  for (int i = 1; i <= m; i++) {
    long score = max(running, prefixes[i]);
    best = min(best, score);
    if (i % 2 == 1) {
      // First/odd row, visit top first then bottom
      long e = 2*(m-i);  //e, e+1
      running = max(running, atop[i] + e + 1);
      running = max(running, adown[i] + e);
    } else {
      long e = 2*(m-i);
      running = max(running, adown[i] + e + 1);
      running = max(running, atop[i] + e);
    }
  }

  cout << best << "\n";

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
