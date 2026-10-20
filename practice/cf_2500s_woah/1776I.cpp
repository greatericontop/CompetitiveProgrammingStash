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
  long x, y;
};


void solve() {
  int n;
  cin >> n;
  vector<Point> points(n);
  FORI(n)  cin >> points[i].x >> points[i].y;
  set<int> active;
  FORI(n)  active.insert(i);

  auto find_best = [&]() -> pairll {
    long best = LLONG_MAX;  int best_i = -1;
    for (auto it = active.begin(); it != active.end(); it++) {
      int i = *it;
      int prev_i = it == active.begin() ? *active.rbegin() : *prev(it);
      int next_i = next(it) == active.end() ? *active.begin() : *next(it);
      Point a = points[prev_i], b = points[i], c = points[next_i];
      // shoelace
      long areadoubled = abs(a.x*b.y + b.x*c.y + c.x*a.y - a.y*b.x - b.y*c.x - c.y*a.x);
      if (areadoubled < best) {
        best = areadoubled;
        best_i = i;
      }
    }
    assert(best_i != -1);
    return {best_i, best};
  };

  auto opponent_turn = [&]() {
    assert(active.size() % 2 == 1);
    int q;  cin >> q;  q--;
    assert(active.count(q));
    active.erase(q);
  };
  auto our_turn = [&]() {
    assert(active.size() % 2 == 0);
    pairll best = find_best();
    cout << best.first + 1 << endl;
    assert(active.count(best.first));
    active.erase(best.first);

    pairll best2 = find_best();
    assert(best2.second >= best.second);
  };

  if (n % 2 == 1) {
    cout << "Beatrice" << endl;
    opponent_turn();
  } else {
    cout << "Alberto" << endl;
  }

  while (true) {
    our_turn();
    assert(active.size() % 2 == 1);
    //if (active.size() <= 2)  break;
    opponent_turn();
    if (active.size() <= 2)  break;
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
