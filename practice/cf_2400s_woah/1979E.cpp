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








struct Point {
  int x;
  int y;

  bool operator < (const Point& other) const {
    if (x != other.x)  return x < other.x;
    return y < other.y;
  }
};
struct Entry {
  int xcoord;
  int which_point;

  bool operator < (const Entry& other) const {
    if (xcoord != other.xcoord)  return xcoord < other.xcoord;
    return which_point < other.which_point;  //just to make set not have duplicates
  }
};


int between(const set<Entry>& s, int x1, int x2) {
  auto it = s.lower_bound({x1, -1});
  if (it == s.end())  return -1;
  if (it->xcoord > x2)  return -1;
  return it->which_point;
}


void solve() {
  int n, d;
  cin >> n >> d;
  d /= 2;
  vector<Point> points(n+1);

  map<Point, int> allpoints;
  map<int, set<Entry>> xplusy;
  map<int, set<Entry>> xminusy;
  FORI1(n) {
    cin >> points[i].x >> points[i].y;
    xplusy[points[i].x + points[i].y].insert({points[i].x, i});
    xminusy[points[i].x - points[i].y].insert({points[i].x, i});
    allpoints[points[i]] = i;
  }

  for (int i = 1; i <= n; i++) {
    int x1 = points[i].x, y1 = points[i].y;
    // try xminusy line
    if (allpoints.count(Point{x1+d, y1+d})) {
      int j = allpoints[Point{x1+d, y1+d}];
      int cur_xminusy = x1 - y1;
      // try cur + 2d, looking for x between x1+d, x1+2d
      int k = between(xminusy[cur_xminusy + 2*d], x1+d, x1+2*d);
      if (k != -1) {
        fprintf(stderr, "j=%d point %d, %d\n", j, points[j].x, points[j].y);
        cout << i << " " << j << " " << k << "\n";
        return;
      }
      // try cur - 2d, looking for x between x1-d, x1
      k = between(xminusy[cur_xminusy - 2*d], x1-d, x1);
      if (k != -1) {
        fprintf(stderr, "j=%d point %d, %d\n", j, points[j].x, points[j].y);
        cout << i << " " << j << " " << k << "\n";
        return;
      }
    }
    // try xplusy line
    if (allpoints.count(Point{x1+d, y1-d})) {
      int j = allpoints[Point{x1+d, y1-d}];
      int cur_xplusy = x1 + y1;
      // try cur - 2d, looking for x between x1-d, x1
      int k = between(xplusy[cur_xplusy - 2*d], x1-d, x1);
      if (k != -1) {
        fprintf(stderr, "j=%d point %d, %d\n", j, points[j].x, points[j].y);
        cout << i << " " << j << " " << k << "\n";
        return;
      }
      // try cur + 2d, looking for x between x1+d, x1+2d
      k = between(xplusy[cur_xplusy + 2*d], x1+d, x1+2*d);
      if (k != -1) {
        fprintf(stderr, "j=%d point %d, %d\n", j, points[j].x, points[j].y);
        cout << i << " " << j << " " << k << "\n";
        return;
      }
    }
  }

  cout << "0 0 0\n";

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
