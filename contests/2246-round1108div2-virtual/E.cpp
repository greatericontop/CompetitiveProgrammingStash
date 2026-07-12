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
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










void solve() {
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

  // 0b 1 [29 zeros]
  int x = 1 << 29;
  cout << x << endl;

  int o;
  cin >> o;
  if (!(o & (1<<29))) {
    // then the operation is & and o[29] = 0
    int m0 = 0, m1 = (1<<30)-1;
    cout << m0 << " " << m1 << endl;
    int r;
    cin >> r;
    if (r & (1<<29)) {
      cout << "1" << endl;
    } else {
      cout << "0" << endl;
    }
    return;
  }
  for (int b = 0; b < 29; b++) {
    if (o & (1<<b)) {
      // then the operation is | and o[b] = 1
      int m0 = 0, m1 = (1<<30)-1;
      cout << m0 << " " << m1 << endl;
      int r;
      cin >> r;
      if (r & (1<<b)) {
        cout << "0" << endl;
      } else {
        cout << "1" << endl;
      }
      return;
    }
  }

  // Otherwise we are either in 1???????? or ?00000000
  int m0 = 0;
  uint64_t rngval = rng();
  int randbits = rngval & ((1<<29)-1);
  // 1 followed by 29 random bits
  int m1 = (1<<29) | (randbits);
  cout << m0 << " " << m1 << endl;
  int r;
  cin >> r;

  int right_half = r & ((1<<29)-1);
  if (right_half == 0) {
    // assume, probablistically, that we are in ?00000000, thus m0 is right
    cout << "0" << endl;
    return;
  } else if (right_half == randbits) {
    // assume, probablistically, that we are in ?00000000
    cout << "1" << endl;
    return;
  } else {
    // assume we are in 1????????
    int msb = (r >> 29) & 1;
    if (msb == 0) {
      cout << "1" << endl;
    } else {
      cout << "0" << endl;
    }
    return;
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
