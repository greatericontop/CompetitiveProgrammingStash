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









struct Segment {
  int start;
  int size;
  int id;
};


void solve() {
  int n;
  cin >> n;
  vector<int> c(2*n);
  FORI(2*n)  cin >> c[i];

  vector<Segment> segs;
  int end = 2*n;
  while (end > 0) {
    int maxval = 0, maxidx = -1;
    for (int i = 0; i < end; i++) {
      if (c[i] > maxval) {
        maxval = c[i];
        maxidx = i;
      }
    }
    segs.pb({maxidx, end - maxidx, -1});
    end = maxidx;
  }
  reverse(segs.begin(), segs.end());
  for (int j = 0; j < segs.size(); j++) {
    segs[j].id = j;
  }
  for (Segment seg : segs) {
    fprintf(stderr, "segment: %d to %d sz=%d\n", seg.start, seg.start + seg.size - 1, seg.size);
  }
  // segs now contains segs in sorted order

  vector<bool> dp(n+1, false);  //reachable or not, 0 to n
  vector<int> parents(n+1, -1);  //parents[i] means that to reach i, we used segs[parents[i]]
  dp[0] = true;
  for (int j = 0; j < segs.size(); j++) {
    for (int x = n; x >= 0; x--) {
      int y = x + segs[j].size;
      if (y > n)  continue;
      // x ---> y
      if (dp[x] && !dp[y]) {
        dp[y] = true;
        parents[y] = j;
      }
    }
  }

  if (!dp[n]) {
    cout << "-1\n";
    return;
  } else {
    vector<bool> used(segs.size(), false);
    int y = n;
    while (y > 0) {
      int j = parents[y];
      assert(j != -1);
      fprintf(stderr, "y = %d, used segment #%d (size %d)\n", y, j, segs[j].size);
      used[j] = true;
      y -= segs[j].size;
    }
    vector<int> a, b;
    for (int j = 0; j < segs.size(); j++) {
      if (used[j]) {
        for (int x = segs[j].start; x < segs[j].start + segs[j].size; x++) {
          a.pb(c[x]);
        }
      } else {
        for (int x = segs[j].start; x < segs[j].start + segs[j].size; x++) {
          b.pb(c[x]);
        }
      }
    }

    assert(a.size() == n && b.size() == n);
    for (int z : a)  cout << z << " ";
    cout << "\n";
    for (int z : b)  cout << z << " ";
    cout << "\n";
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
