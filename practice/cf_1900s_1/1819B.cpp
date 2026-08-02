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









struct Rect {
  int x;
  int y;
};


bool is_possible(long xmax, long ymax, const vector<Rect>& rects) {
  auto max_x_cmp = [](const Rect& a, const Rect& b) {
    if (a.x != b.x)  return a.x > b.x;
    return a.y > b.y;
  };
  auto max_y_cmp = [](const Rect& a, const Rect& b) {
    if (a.y != b.y)  return a.y > b.y;
    return a.x > b.x;
  };
  multiset<Rect, decltype(max_x_cmp)> max_x_set(max_x_cmp);
  multiset<Rect, decltype(max_y_cmp)> max_y_set(max_y_cmp);
  for (Rect r : rects) {
    max_x_set.insert(r);
    max_y_set.insert(r);
  }

  fprintf(stderr, "begin loop\n");
  while (!max_x_set.empty()) {
    fprintf(stderr, "xmax = %ld ymax = %ld\n", xmax, ymax);
    Rect r_x = *max_x_set.begin();
    Rect r_y = *max_y_set.begin();
    // fail immediately if either rectangle overflows
    if (r_x.x > xmax || r_x.y > ymax || r_y.x > xmax || r_y.y > ymax) {
      fprintf(stderr, "rectangle too big: r_x=(%d,%d) r_y=(%d,%d) xmax=%ld ymax=%ld\n", r_x.x, r_x.y, r_y.x, r_y.y, xmax, ymax);
      return false;
    }
    // if r_x works, then use it
    // if r_x is too small, then try r_y
    if (r_x.x == xmax) {
      max_x_set.erase(max_x_set.find(r_x));
      max_y_set.erase(max_y_set.find(r_x));
      ymax -= r_x.y;
    } else if (r_y.y == ymax) {
      max_x_set.erase(max_x_set.find(r_y));
      max_y_set.erase(max_y_set.find(r_y));
      xmax -= r_y.x;
    } else {
      fprintf(stderr, "no rectangle fits: r_x=(%d,%d) r_y=(%d,%d) xmax=%ld ymax=%ld\n", r_x.x, r_x.y, r_y.x, r_y.y, xmax, ymax);
      return false;
    }
  }

  // also make sure we are done at this point
  fprintf(stderr, "finished: xmax=%ld ymax=%ld\n", xmax, ymax);
  return xmax == 0 || ymax == 0;
}


void solve() {
  int n;
  cin >> n;
  vector<Rect> rects(n);
  FORI(n)  cin >> rects[i].x >> rects[i].y;
  long area = 0;
  FORI(n)  area += LONG(rects[i].x) * LONG(rects[i].y);
  long xmax = -1;
  long ymax = -1;
  FORI(n) {
    xmax = max<long>(xmax, rects[i].x);
    ymax = max<long>(ymax, rects[i].y);
  }
  fprintf(stderr, "area=%ld xmax=%ld ymax=%ld\n", area, xmax, ymax);

  vector<pairll> answers;

  // xmax, area/xmax
  if (area % xmax == 0) {
    long y = area / xmax;
    assert(xmax * y == area);
    fprintf(stderr, "try %ld, %ld\n", xmax, y);
    if (is_possible(xmax, y, rects)) {
      answers.pb({xmax, y});
    }
  }
  // ymax, area/ymax
  if (area % ymax == 0) {
    long x = area / ymax;
    assert(x * ymax == area);
    fprintf(stderr, "try %ld, %ld\n", x, ymax);
    if (is_possible(x, ymax, rects)) {
      answers.pb({x, ymax});
    }
  }

  if (answers.size() == 2 && answers[0] == answers[1]) {
    answers.pop_back();
  }

  cout << answers.size() << "\n";
  for (pairll p : answers) {
    cout << p.first << " " << p.second << "\n";
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
