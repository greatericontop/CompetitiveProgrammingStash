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


  vector<vector<pairii>> to_open(n);
  vector<vector<pairii>> to_close(n);
  // interval i to i+1
  for (int i = 0; i < n; i++) {
    Point p1 = points[i];
    Point p2 = points[i+1];
    fprintf(stderr, "p1(%d, %d) p2(%d, %d)\n", p1.x, p1.y, p2.x, p2.y);
    long multi_x = p2.x - p1.x, multi_y = p2.y - p1.y;
    auto score = [&](Point p) {
      return LONG(p.x)*multi_x + LONG(p.y)*multi_y;
    };
    fprintf(stderr, "score(p1) = %ld, score(p2)=%ld\n", score(p1), score(p2));
    assert(score(p1) <= score(p2));  long diff = score(p2) - score(p1);

    auto which = [&](Point p) {
      long delta = score(p) - score(p1);
      if (diff % 2 == 0 && delta == diff/2)  return 2;  // a == will be considered an open
      return delta > diff/2 ? 2 : 1;  //closer to p1 or closer to p2
    };
    // "opens" = closer to p2

    assert(which(p1) == 1);  assert(which(p2) == 2);
    // want to find the index where it switches
    // want l to point to 2 and r to point to 1
    int l = i+1, r = i + n;
    while (l + 1 < r) {
      int mid = l + (r-l)/2;
      if (which(points[mid]) == 2) {
        l = mid;
      } else {
        r = mid;
      }
    }
    //fprintf(stderr, "should open (closer to right) between %d...%d and close (closer to left) %d...%d\n", i+1, l, r, i+n);
    //so open between i+1 and l
    {
      int l1 = (r) % n;
      int r1 = (i+n) % n;
      if (l1 <= r1) {
        to_open[i].pb({l1, r1});
      } else {
        to_open[i].pb({0, r1});
        to_open[i].pb({l1, n-1});
      }
    }
    //close between r and i+n
    {
      int l1 = (i+1) % n;
      int r1 = (l) % n;
      if (l1 <= r1) {
        to_close[i].pb({l1, r1});
      } else {
        to_close[i].pb({0, r1});
        to_close[i].pb({l1, n-1});
      }
    }
  }

  vector<int> closest_points(n);
  set<int> waiting_to_open;  for (int i = 0; i < n; i++)  waiting_to_open.insert(i);
  set<int> opened;

  for (int i = 0; i < 2*n; i++) {
    int imodded = i % n;

    for (auto [l, r] : to_open[imodded]) {
      auto it = waiting_to_open.lower_bound(l);
      while (it != waiting_to_open.end() && *it <= r) {
        opened.insert(*it);
        it = waiting_to_open.erase(it);
      }
    }
    for (auto [l, r] : to_close[imodded]) {
      auto it = opened.lower_bound(l);
      while (it != opened.end() && *it <= r) {
        closest_points[*it] = imodded;
        it = opened.erase(it);
      }
    }
  }

  PRINTVEC(closest_points);

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
  for (int i1 = 0; i1 < n; i1++) {
    Point _p = points[closest_points[i1]];
    long best_distance_squared = distancesquared(_p, points[i1]);
    for (int i2 = closest_points[i1]; true; i2--) {
      int i2mod = (i2 + n) % n;
      if (distancesquared(points[i1], points[i2mod]) >= best_distance_squared) {
        assert(distancesquared(points[i1], points[i2mod]) == best_distance_squared);
        update(distancesquared(points[i1], points[i2mod]));
      } else {
        break;
      }
    }
    for (int i2 = closest_points[i1]+1; true; i2++) {
      int i2mod = (i2 + n) % n;
      if (distancesquared(points[i1], points[i2mod]) >= best_distance_squared) {
        assert(distancesquared(points[i1], points[i2mod]) == best_distance_squared);
        update(distancesquared(points[i1], points[i2mod]));
      } else {
        break;
      }
    }
  }
  assert(how_many % 2 == 0);  //each arc should be drawn exactly twice
  how_many /= 2;
  fprintf(stderr, "best dist squared %ld x%ld\n", best_distance_squared, how_many);
  best_distance_squared *= 4;  //twice as long

  int l = 0, r = 1e9;
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
