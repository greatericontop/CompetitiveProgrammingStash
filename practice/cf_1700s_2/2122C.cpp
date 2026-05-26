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
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }










struct Point {
  int x;
  int y;
  int idx;
};

void solve() {
  int n;
  cin >> n;
  vector<Point> points(n);
  FORI(n) {
    cin >> points[i].x >> points[i].y;
    points[i].idx = i;
  }

  sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.x < b.x;
  });
  vector<bool> leftright(n);
  for (int i = 0; i < n; i++) {
    leftright[points[i].idx] = (i >= n/2);
  }

  sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.y < b.y;
  });
  vector<Point> lefttop, righttop, leftdown, rightdown;

  for (int i = 0; i < n; i++) {
    if (leftright[points[i].idx]) {
      if (i >= n/2)  righttop.pb(points[i]);
      else  rightdown.pb(points[i]);
    } else {
      if (i >= n/2)  lefttop.pb(points[i]);
      else  leftdown.pb(points[i]);
    }
  }


  assert(lefttop.size() == rightdown.size());
  assert(leftdown.size() == righttop.size());

  for (int i = 0; i < lefttop.size(); i++) {
    cout << lefttop[i].idx + 1 << " " << rightdown[i].idx + 1 << "\n";
  }
  for (int i = 0; i < leftdown.size(); i++) {
    cout << leftdown[i].idx + 1 << " " << righttop[i].idx + 1 << "\n";
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
