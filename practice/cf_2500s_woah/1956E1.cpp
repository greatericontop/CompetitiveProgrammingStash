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








constexpr int LVL = 650;
struct State {
  int data[LVL];
  //bool zero;
};


void solve() {
  int n;
  cin >> n;
  vector<int> b(n);
  FORI(n)  cin >> b[i];

  // first pass to find somewhere to unroll the loop
  int i0 = -1;
  for (int t = 0; t < LVL; t++) {  //sqrt decomp argument, 0 must show up within 650
    for (int i = 0; i < n; i++) {
      b[(i+1)%n] = max(b[(i+1)%n]-b[i], 0);
      if (b[(i+1)%n] == 0) {
        // make the new starting point
        fprintf(stderr, "found at t = %d\n", t);
        i0 = (i+2)%n;
        goto breakouter;
      }
    }
  }
  breakouter:
  //if (i0 == -1)  return;
  assert(i0 != -1);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = b[(i+i0)%n];
  }
  fprintf(stderr, "i0 = %d\n", i0);
  PRINTVEC(a);

  vector<bool> zf(n);
  State sprev;
  for (int i = 0; i < LVL; i++)  sprev.data[i] = a[0];
  zf[0] = (a[0] == 0);
  for (int i = 1; i < n; i++) {
    State scur;
    scur.data[0] = a[i];
    // after round 1, we start from [0] and subtract the final value of the previous one after round 1
    for (int j = 1; j < LVL; j++) {
      scur.data[j] = scur.data[j-1] - sprev.data[j];
      scur.data[j] = max(scur.data[j], 0);
    }
    if (scur.data[LVL-1] == 0) {
      // if already zero
      zf[i] = true;
    } else {
      // if nonzero, then we are zero if the previous one wasn't
      zf[i] = !zf[i-1];
      if (zf[i-1]) {
        // if zero flag for previous, we should've hit it by now (else we would have already been 0)
        assert(sprev.data[LVL-1] == 0);
      }
    }

    sprev = scur;

    fprintf(stderr, "i=%d, a[i]=%d, first few: %d %d %d %d %d zf: %s\n", i, a[i], s[i].data[0], s[i].data[1], s[i].data[2], s[i].data[3], s[i].data[4], s[i].zero ? "zero" : "nonzero");
  }

  int nonzero_ct = 0;
  vector<int> nonzero_idx;
  for (int i = 0; i < n; i++) {
    if (!zf[i]) {
      nonzero_ct++;
      nonzero_idx.pb((i+i0)%n +1);
    }
  }
  sort(nonzero_idx.begin(), nonzero_idx.end());
  cout << nonzero_ct << "\n";
  for (int x : nonzero_idx) {
    cout << x << " ";
  }
  cout << "\n";

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
