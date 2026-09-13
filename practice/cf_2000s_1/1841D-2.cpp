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
  int l, r;

  bool operator < (const Segment& other) const {
    if (l != other.l)  return l < other.l;
    return r < other.r;  //the shorter one is taken first
  }
};

void solve() {
  int n;
  cin >> n;
  vector<Segment> a(n);
  FORI(n)  cin >> a[i].l >> a[i].r;
  vector<int> coords;
  FORI(n) {
    coords.pb(a[i].l);
    coords.pb(a[i].r);
  }
  sort(coords.begin(), coords.end());
  coords.erase(unique(coords.begin(), coords.end()), coords.end());
  int m = coords.size();  assert(m <= 2 * n);
  vector<vector<int>> segment_at(m);
  FORI(n) {
    a[i].l = lower_bound(coords.begin(), coords.end(), a[i].l) - coords.begin();
    a[i].r = lower_bound(coords.begin(), coords.end(), a[i].r) - coords.begin();
    segment_at[a[i].l].pb(i);
    assert(a[i].l >= 0 && a[i].l < m);
    assert(a[i].r >= 0 && a[i].r < m);
  }
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "Segment %d: [%d, %d]\n", i, a[i].l, a[i].r);
  }

  vector<int> dp(m+1, 0);
  for (int i = m-1; i >= 0; i--) {
    dp[i] = dp[i+1];

    for (int seg_id : segment_at[i]) {
      Segment s1 = a[seg_id];  assert(s1.l == i);
      for (int seg2_id = 0; seg2_id < n; seg2_id++) {
        if (seg2_id == seg_id)  continue;
        Segment s2 = a[seg2_id];
        if (s2.l < i)  continue;  //can't be to the left of i
        int intersect_l = max(s1.l, s2.l);
        int intersect_r = min(s1.r, s2.r);
        if (intersect_l <= intersect_r) {
          dp[i] = max(dp[i], 1 + dp[max(s1.r, s2.r) + 1]);
        }
      }
    }

    fprintf(stderr, "dp[%d] = %d\n", i, dp[i]);
  }

  int most_segs = 2*dp[0];
  int ans = n - most_segs;
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
