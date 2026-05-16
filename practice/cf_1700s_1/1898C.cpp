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
  int n, m, k;
  cin >> n >> m >> k;
  int shortest_path = n + m - 2;
  if (k < shortest_path || (k - shortest_path) % 2 != 0) {
    cout << "NO\n";
    return;
  }

  char a[2] = {'R', 'B'};
  vector<vector<char>> horiz_edges(n, vector<char>(m-1, 'R'));
  for (int i = 0; i < m-1; i++) {
    horiz_edges[0][i] = a[i % 2];
    horiz_edges[0][i] = a[i % 2];
  }
  horiz_edges[1][0] = 'R';

  vector<vector<char>> vert_edges(n-1, vector<char>(m, 'R'));
  for (int i = 0; i < n-1; i++) {
    vert_edges[i][m-1] = a[(m+1+i) % 2];
  }
  vert_edges[0][0] = 'B';
  vert_edges[0][1] = 'B';

  int diff = k - shortest_path;
  if (diff % 4 == 2) {
    horiz_edges[0][0] = 'B';
    horiz_edges[1][0] = 'B';
    vert_edges[0][0] = 'R';
    vert_edges[0][1] = 'R';
  }

  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m-1; j++) {
      cout << horiz_edges[i][j] << " ";
    }
    cout << "\n";
  }
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < m; j++) {
      cout << vert_edges[i][j] << " ";
    }
    cout << "\n";
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
