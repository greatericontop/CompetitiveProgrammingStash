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






using int128 = __int128;

struct Point {
  int x, y;
};

void solve() {
  int n, k;
  cin >> n >> k;
  vector<Point> points(3*n);
  FORI(n) {
    cin >> points[i].x >> points[i].y;
    points[i+n] = points[i];
    points[i+2*n] = points[i];
  }




  // Find farthest distance and how many
  long best_distance_squared = 0;
  long how_many = 0;
  auto update = [&](long x) {
    if (x > best_distance_squared) {
      best_distance_squared = x;
      how_many = 1;
    } else if (x == best_distance_squared) {
      how_many++;
    }
  };
  auto distancesquared = [](Point p1, Point p2) {
    return LONG(p2.x-p1.x)*LONG(p2.x-p1.x) + LONG(p2.y-p1.y)*LONG(p2.y-p1.y);
  };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      long dsq = distancesquared(points[i], points[j]);
      assert(dsq <= 2e18);
      update(dsq);
    }
  }
  assert(how_many % 2 == 0);  //each arc should be drawn exactly twice
  how_many /= 2;
  fprintf(stderr, "best dist squared %ld x%ld\n", best_distance_squared, how_many);
  best_distance_squared *= 4;  //twice as long

  int l = 0, r = 2e9;
  while (l < r) {
    int mid = l + (r-l)/2;
    int128 totald2 = ((int128)mid)*((int128)mid)*((int128)best_distance_squared);
    if (mid > how_many)  totald2--;
    if (totald2 >= LONG(k)*LONG(k)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  assert(l <= 1e9);

  cout << l << "\n";
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
