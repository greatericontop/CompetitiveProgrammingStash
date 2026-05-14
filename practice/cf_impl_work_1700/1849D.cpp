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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  vector<bool> good(n, false);
  int num_segments = 0;
  int seg_start = 0;
  bool seg_seen_2 = false;
  for (int i = 0; i < n; i++) {
    if (seg_start-1 >= 0)  assert(a[seg_start-1] == 0);

    if (a[i] == 2) {
      seg_seen_2 = true;
      good[i] = true;
    } else if (a[i] == 1) {
      good[i] = true;
    } else {  //0
      if (seg_start < i) {
        // process previous segment
        num_segments++;
        if (seg_seen_2) {
          if (seg_start-1 >= 0)  good[seg_start-1] = true;
          if (i < n)  good[i] = true;
        } else {
          // good the left one, or if already then the right one
          if (seg_start-1 >= 0 && !good[seg_start-1]) {
            good[seg_start-1] = true;
          } else if (i < n) {
            good[i] = true;
          }
        }

        seg_start = i+1;
        seg_seen_2 = false;
      } else {
        seg_start = i+1;
        seg_seen_2 = false;
      }
    }
  }
  if (seg_start < n) {
    num_segments++;
    if (seg_seen_2) {
      if (seg_start-1 >= 0)  good[seg_start-1] = true;
    } else {
      if (seg_start-1 >= 0 && !good[seg_start-1]) {
        good[seg_start-1] = true;
      }
    }
  }

  int not_good = 0;
  for (int i = 0; i < n; i++) {
    if (!good[i]) {
      assert(a[i] == 0);
      not_good++;
    }
  }
  fprintf(stderr, "num_segments: %d, not_good: %d\n", num_segments, not_good);
  int cost = num_segments + not_good;
  cout << cost << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
