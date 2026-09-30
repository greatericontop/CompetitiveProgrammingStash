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



int xors[8];
int covers[8];






void solve() {
  for (int m = 0; m < 8; m++) {
    int a = m >> 2, b = (m >> 1) & 1, c = m & 1;
    int ab = a ^ b, bc = b ^ c, ac = a ^ c;
    assert(0 <= ab && ab <= 1 && 0 <= bc && bc <= 1 && 0 <= ac && ac <= 1);
    xors[m] = (ab << 2) | (bc << 1) | ac;
    if (ab + bc + ac == 2) {
      // then covered[m] = which index 0(ab), 1(bc), 2(ac) is covered
      if (ab == 0)  covers[m] = 4;
      else if (bc == 0)  covers[m] = 2;
      else  covers[m] = 1;
    } else {
      covers[m] = -1;
    }
  }
  for (int m = 0; m < 8; m++) {
    fprintf(stderr, "mask %d has xors %d and covers %d\n", m, xors[m], covers[m]);
  }
  string s;
  cin >> s;
  vector<vector<long>> dp_old(8, vector<long>(8, 0));
  vector<vector<long>> dp_new(8, vector<long>(8, 0));
  // initially nothing is free and nothing is covered
  dp_old[0][0] = 1;

  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    fprintf(stderr, "  i = %d\n", i);
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        dp_new[i][j] = 0;
      }
    }

    for (int free = 0; free < 8; free++) {
      for (int covered = 0; covered < 8; covered++) {
        for (int o = 0; o < 8; o++) {
          // want to use o for assignments of a, b, c
          // assignment is invalid if c=='0' and a bit is 1 while it is not free
          if (c == '0' && (o & ~free))  continue;

          int new_free = free;
          if (c == '1') {
            // then set bits in new_free if n has a 1 while o is 0
            // remember freeness is between o and n!!!!!!!!
            new_free |= (~o) & 0b111;
          }

          int new_covered = covered;
          if (covers[o] != -1) {
            new_covered |= covers[o];
          }

          fprintf(stderr, "[%d][%d] -> [%d][%d] (+%ld)\n", free, covered, new_free, new_covered, dp_old[free][covered]);
          dp_new[new_free][new_covered] += dp_old[free][covered];
          dp_new[new_free][new_covered] %= MOD;
        }
      }
    }

    swap(dp_old, dp_new);
  }

  long ans = 0;
  for (int free = 0; free < 8; free++) {
    ans += dp_old[free][0b111];
    ans %= MOD;
  }
  cout << ans << "\n";

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
