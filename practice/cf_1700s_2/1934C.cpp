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
  int n, m;
  cin >> n >> m;
  int first_band;
  int second_band;

  cout << "? 1 1" << endl;
  int x1; cin >> x1;
  first_band = x1 + 2;  //the line x + y = first_band
  cout << "? " << n << " " << m << endl;
  int x2; cin >> x2;
  second_band = (n+m) - (x2);
  fprintf(stderr, "first_band: %d, second_band: %d\n", first_band, second_band);

  cout << "? " << 1 << " " << (second_band-1) << endl;
  int x3; cin >> x3;
  pair<int, int> second_band_point = {1 + x3/2, (second_band-1) - x3/2};
  int x4 = x3 - (second_band - first_band);
  pair<int, int> first_band_point;
  if (x4 % 2 == 0) {
    first_band_point = {1 + x4/2, (first_band-1) - x4/2};
  } else {
    first_band_point = {-1, -1};
  }

  cout << "? " << second_band_point.first << " " << second_band_point.second << endl;
  int x5; cin >> x5;
  if (x5 == 0) {
    cout << "! " << second_band_point.first << " " << second_band_point.second << endl;
  } else {
    cout << "! " << first_band_point.first << " " << first_band_point.second << endl;
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
