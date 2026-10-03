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








struct Segment {
  long sum;
  long best_prefixsum;
  long best_suffixsum;
  long best_subarraysum;
  bool invert;
};
Segment combine(const Segment& s1, const Segment& s2, bool invert) {
  const Segment& left = invert ? s2 : s1;
  const Segment& right = invert ? s1 : s2;
  Segment result;
  result.sum = left.sum + right.sum;
  result.best_prefixsum = max(left.best_prefixsum, left.sum + right.best_prefixsum);
  result.best_suffixsum = max(right.best_suffixsum, right.sum + left.best_suffixsum);
  result.best_subarraysum = max(max(left.best_subarraysum, right.best_subarraysum), left.best_suffixsum + right.best_prefixsum);
  result.invert = invert;
  return result;
}


void solve() {
  int n;  cin >> n;
  int expn = 1 << n;
  vector<long> a(expn+1);
  FORI1(expn)  cin >> a[i];

  // layer 0 indexes 2^0 + 1 (2)
  // layer 1 indexes 2^1 + 1,2 (3...4)
  // layer 2 indexes 2^2 + 1,2,3,4 (5...8)
  // ...
  // layer n indexes 2^n + 1...2^n (each element themselves)
  vector<Segment> segtree(2*expn+1);
  for (int i = 1; i <= expn; i++) {
    segtree[expn + i] = {
      .sum = a[i],
      .best_prefixsum = max<long>(a[i], 0),
      .best_suffixsum = max<long>(a[i], 0),
      .best_subarraysum = max<long>(a[i], 0),
      .invert = false,
    };
  }
  for (int i = expn; i >= 2; i--) {
    segtree[i] = combine(segtree[2*i-1], segtree[2*i], segtree[i].invert);
  }

  auto recombine_layer = [&](int layer) {
    for (int i = (1<<layer) + 1; i <= (1<<layer)*2; i++) {
      segtree[i] = combine(segtree[2*i-1], segtree[2*i], segtree[i].invert);
    }
  };
  auto flip_layer = [&](int layer) {
    for (int i = (1<<layer) + 1; i <= (1<<layer)*2; i++) {
      segtree[i].invert = !segtree[i].invert;
    }
    for (int l = layer; l >= 0; l--) {
      recombine_layer(l);
    }
  };

  vector<long> answers(expn+1);
  // for i=0, the answer is the existing
  answers[0] = segtree[2].best_subarraysum;
  // this is the reversed bits in the query, i[0] means swapping n-1 (aka layer 0)
  for (int i = 1; i <= expn; i++) {
    int flips = i ^ (i-1);
    for (int b = 0; b < n; b++) {
      // The MSB is actually the lowest layer here
      if (flips & (1 << b)) {
        flip_layer(b);
      }
    }
    answers[i] = segtree[2].best_subarraysum;
  }


  // answer queries
  int state = 0;
  int q;  cin >> q;
  while (q --> 0) {
    int k;  cin >> k;
    int bitpos = n-1 - k;
    state ^= 1 << bitpos;

    cout << answers[state] << "\n";
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
