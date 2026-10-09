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









struct Point {
  int x, y;
};
void printanswer(vector<pair<Point, Point>> ans) {
  cout << ans.size() << "\n";
  for (const auto& [p1, p2] : ans) {
    cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";
  }
}

void noncollinear(Point a, Point b, Point c) {
  if (a.y <= c.y) {
    // right-up
    if (a.y <= b.y && b.y <= c.y) {
      printanswer({
        {a, Point{a.x, b.y}},
        {Point{a.x, b.y}, Point{c.x, b.y}},
        {Point{c.x, b.y}, c},
      });
    } else {
      printanswer({
        {a, Point{a.x, c.y}},
        {Point{a.x, c.y}, c},
        {Point{b.x, c.y}, b},
      });
    }
  } else {
    // right-down
    if (c.y <= b.y && b.y <= a.y) {
      printanswer({
        {a, Point{a.x, b.y}},
        {Point{a.x, b.y}, Point{c.x, b.y}},
        {Point{c.x, b.y}, c},
      });
    } else {
      printanswer({
        {a, Point{a.x, c.y}},
        {Point{a.x, c.y}, c},
        {Point{b.x, c.y}, b},
      });
    }
  }
}


void solve() {
  vector<Point> p(3);
  cin >> p[0].x >> p[0].y >> p[1].x >> p[1].y >> p[2].x >> p[2].y;
  sort(p.begin(), p.end(), [](const Point& a, const Point& b) {
    if (a.x != b.x)  return a.x < b.x;
    return a.y < b.y;
  });
  Point a = p[0], b = p[1], c = p[2];

  if (a.x != b.x && b.x != c.x) {
    noncollinear(a, b, c);
  } else if (a.x == b.x && b.x == c.x) {
    assert(a.y <= b.y && b.y <= c.y);
    printanswer({
      {a, c},
    });
  } else {
    // two are collinear
    if (a.x == c.x)  swap(b, c);
    if (b.x == c.x)  swap(a, c);
    assert(a.x == b.x && b.x != c.x);

    int shared_x = a.x;
    int other_x = c.x;
    int miny = min(a.y, min(b.y, c.y));
    int maxy = max(a.y, max(b.y, c.y));
    printanswer({
      {Point{shared_x, miny}, Point{shared_x, maxy}},
      {c, Point{shared_x, c.y}},
    });
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
