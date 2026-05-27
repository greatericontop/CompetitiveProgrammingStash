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










void solve() {
  int n;
  cin >> n;
  vector<string> grid(n);
  FORI(n)  cin >> grid[i];

  set<int> xplusy_diagonals;
  set<int> xminusy_diagonals;
  int xmin = n+1, ymin = n+1, xmax = -1, ymax = -1;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '#') {
        xplusy_diagonals.insert(i + j);
        xminusy_diagonals.insert(i - j);
        xmin = min(xmin, i);
        xmax = max(xmax, i);
        ymin = min(ymin, j);
        ymax = max(ymax, j);
      }
    }
  }

  // Win condition 1: adjacent x + y diagonals
  if (xplusy_diagonals.size() <= 1) {
    cout << "YES\n";
    return;
  }
  if (xplusy_diagonals.size() == 2 && *xplusy_diagonals.begin() + 1 == *xplusy_diagonals.rbegin()) {
    cout << "YES\n";
    return;
  }
  // adjacent x - y diagonals
  if (xminusy_diagonals.size() <= 1) {
    cout << "YES\n";
    return;
  }
  if (xminusy_diagonals.size() == 2 && *xminusy_diagonals.begin() + 1 == *xminusy_diagonals.rbegin()) {
    cout << "YES\n";
    return;
  }
  // bounding box is 2x2
  if (xmax - xmin <= 1 && ymax - ymin <= 1) {
    cout << "YES\n";
    return;
  }

  cout << "NO\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
