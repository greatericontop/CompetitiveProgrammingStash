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
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> a(x);
  FORI(x)  cin >> a[i];
  sort(a.begin(), a.end());

  int score = 0;
  int two_gaps = 0;
  vector<int> even_gaps;
  vector<int> odd_gaps;
  for (int i = 0; i < x; i++) {
    int gap = i == x-1 ? (n - a[i] + a[0]) : (a[i+1] - a[i]);
    if (gap == 2) {
      two_gaps++;
    } else if (gap % 2 == 0) {
      even_gaps.push_back(gap);
    } else {
      odd_gaps.push_back(gap);
    }
  }
  sort(even_gaps.begin(), even_gaps.end());
  sort(odd_gaps.begin(), odd_gaps.end());

  for (int g : even_gaps) {
    if (y >= (g-2)/2) {
      y -= (g-2)/2;
      two_gaps += g/2;
      score += (g-2)/2;
    } else {
      two_gaps += y;
      score += y;
      y = 0;
    }
  }

  for (int g : odd_gaps) {
    if (y >= g / 2) {
      y -= g / 2;
      two_gaps += g / 2;
      score += g / 2;
    } else {
      two_gaps += y;
      score += y;
      y = 0;
    }
  }

  cout << (x + score - 2 + two_gaps) << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
