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








struct Block {
  int big;
  int small;
  int ct;

  bool operator < (const Block& other) const {
    if (big != other.big)  return big < other.big;
    return small < other.small;
    // do not compare by ct
  }
};


void solve() {
  int n;
  cin >> n;
  vector<long> factorials(n+2, 1);
  for (int i = 1; i < n+2; i++) {
    factorials[i] = (factorials[i-1] * LONG(i)) % MOD;
  }
  set<Block> blocks;
  FORI(n) {
    int l, w;  cin >> l >> w;
    if (l < w)  swap(l, w);
    Block b = {.big = l, .small = w, .ct = 1};
    auto it = blocks.find(b);
    if (it == blocks.end()) {
      blocks.insert(b);
    } else {
      Block old = *it;
      blocks.erase(it);
      old.ct += 1;
      blocks.insert(old);
    }
  }

  vector<Block> blocksvec;  blocksvec.reserve(blocks.size());
  for (Block b : blocks)  blocksvec.pb(b);
  sort(blocksvec.begin(), blocksvec.end(), [](Block b1, Block b2) {
    return b2 < b1;
  });
  for (Block b : blocksvec) {
    fprintf(stderr, "Block{%d,%d  x%d}\n", b.big, b.small, b.ct);
  }


  long answer = 1;
  Block cur = blocksvec[0];
  if (cur.big != cur.small)  answer *= 2;  //first block may be placed in two orientations
  answer *= factorials[cur.ct];
  answer %= MOD;

  for (int i = 1; i < blocksvec.size(); i++) {
    Block next = blocksvec[i];
    // ensure that they fit
    assert(next.big <= cur.big);
    if (next.small > cur.small) {
      // then these two will not fit in each other
      answer = 0;
    } else {
      // placements
      long placements = 0;
      {
        //long way
        int spacex = cur.big - next.big + 1;
        int spacey = cur.small - next.small + 1;
        placements += LONG(spacex)*LONG(spacey);
        placements %= MOD;
      }
      if (next.small != next.big) {
        //short way
        int spacex = cur.small - next.big + 1;
        int spacey = cur.big - next.small + 1;
        if (spacex >= 0 && spacey >= 0) {
          placements += LONG(spacex)*LONG(spacey);
          placements %= MOD;
        }
      }
      fprintf(stderr, "i=%d placements %ld\n", i, placements);

      long ordering = factorials[next.ct];
      answer *= placements * ordering;
      answer %= MOD;
    }

    cur = next;
  }

  cout << answer << "\n";

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
