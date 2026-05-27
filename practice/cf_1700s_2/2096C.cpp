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










constexpr static long INF = LONG(1e18);

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> h(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> h[i][j];
    }
  }
  vector<int> a(n);  //rows
  FORI(n)  cin >> a[i];
  vector<int> b(n);  //cols
  FORI(n)  cin >> b[i];


  // Solve rows
  vector<vector<long>> dprow(n, vector<long>(2, INF));
  dprow[0][0] = 0;
  dprow[0][1] = a[0];
  for (int i = 1; i < n; i++) {
    for (int prev = 0; prev < 2; prev++) {
      for (int cur = 0; cur < 2; cur++) {
        bool works = true;
        for (int j = 0; j < n; j++) {
          int prevh = h[i-1][j] + prev;
          int curh = h[i][j] + cur;
          if (prevh == curh) {
            works = false;
            break;
          }
        }
        if (works) {
          dprow[i][cur] = min(dprow[i][cur], dprow[i-1][prev] + cur*a[i]);
        }
      }
    }
  }

  // Solve cols
  vector<vector<long>> dpcol(n, vector<long>(2, INF));
  dpcol[0][0] = 0;
  dpcol[0][1] = b[0];
  for (int j = 1; j < n; j++) {
    for (int prev = 0; prev < 2; prev++) {
      for (int cur = 0; cur < 2; cur++) {
        bool works = true;
        for (int i = 0; i < n; i++) {
          int prevh = h[i][j-1] + prev;
          int curh = h[i][j] + cur;
          if (prevh == curh) {
            works = false;
            break;
          }
        }
        if (works) {
          dpcol[j][cur] = min(dpcol[j][cur], dpcol[j - 1][prev] + cur * b[j]);
        }
      }
    }
  }


  long ans = min(dprow[n-1][0], dprow[n-1][1]) + min(dpcol[n-1][0], dpcol[n-1][1]);
  if (ans >= INF)  ans = -1;
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
