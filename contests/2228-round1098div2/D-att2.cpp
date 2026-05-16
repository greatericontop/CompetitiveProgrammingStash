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

  void print() const {
    fprintf(stderr, "(%d, %d) ", x, y);
  }
};

void solve() {
  int n;
  cin >> n;
  vector<Point> points(n);
  set<int> all_x_coordinates_s;
  for (int i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
    all_x_coordinates_s.insert(points[i].x);
  }
  vector<int> all_x_coordinates;
  for (int x : all_x_coordinates_s)  all_x_coordinates.pb(x);
  vector<int> coord_to_index(n+1);
  for (int i = 0; i < (int) all_x_coordinates.size(); i++) {
    coord_to_index[all_x_coordinates[i]] = i;
  }
  auto by_x = [](const Point& a, const Point& b) {
    if (a.x != b.x)  return a.x < b.x;
    return a.y < b.y;
  };
  auto by_y = [](const Point& a, const Point& b) {
    return a.y < b.y;
  };
  sort(points.begin(), points.end(), by_y);


  //precompute prefix/suffix min/max to save time in the loop
  vector<int> prefix_max(n);
  vector<int> prefix_min(n);
  prefix_min[0] = points[0].x;
  prefix_max[0] = points[0].x;
  for (int i = 1; i < n; i++) {
    prefix_min[i] = min(prefix_min[i-1], points[i].x);
    prefix_max[i] = max(prefix_max[i-1], points[i].x);
  }
  vector<int> suffix_max(n);
  vector<int> suffix_min(n);
  suffix_min[n-1] = points[n-1].x;
  suffix_max[n-1] = points[n-1].x;
  for (int i = n-2; i >= 0; i--) {
    suffix_min[i] = min(suffix_min[i+1], points[i].x);
    suffix_max[i] = max(suffix_max[i+1], points[i].x);
  }


  long ans = 0;
  // Sweep
  for (int i = 0; i < n; i++) {
    if (i < n-1 && points[i].y == points[i+1].y) {
      // process next point before calculating
      continue;
    }
    if (i == n-1) {
      // guaranteed points in top and bottom
      continue;
    }

    int xmin = max(prefix_min[i], suffix_min[i+1]);
    int xmax = min(prefix_max[i], suffix_max[i+1]);
    if (xmax < xmin) {
      continue;
    }
    int it2 = coord_to_index[xmax];
    int it1 = coord_to_index[xmin];
    assert(it2 - it1 >= 0);
    ans += it2 - it1;
  }

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
