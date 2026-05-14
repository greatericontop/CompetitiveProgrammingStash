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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










void solve() {
  int n; long m;
  cin >> n >> m;
  vector<long> a(n);
  FORI(n)  cin >> a[i];
  vector<pair<long, int>> a_sorted(n);
  FORI(n)  a_sorted[i] = {a[i], i};
  sort(a_sorted.begin(), a_sorted.end());

  // how many opponents beat us
  int low = 0, high = n;
  while (low < high) {
    int loseto = low + (high-low)/2;
    fprintf(stderr, "lose to %d (%d'th place)\n", loseto, loseto+1);

    // Option 1: beat n-loseto opponents, so we only lose to [n-loseto+1, ..., n]
    long total = 0;
    for (int i = 0; i < n-loseto; i++) {
      total += a_sorted[i].first;
    }
    fprintf(stderr, "  beat opponents total: %lld\n", total);
    if (total <= m) {
      high = loseto;
      continue;
    }

    // Option 2
    long winct = n - loseto - 2;
    int winct_idx = n - loseto - 1;
    // have to beat opponent [winct]
    long total2 = a[winct_idx];
    int i = 0;
    while (winct > 0) {
      if (a_sorted[i].second == winct_idx) {
        i++;
        continue;
      }
      total2 += a_sorted[i].first;
      i++;
      winct--;
    }
    fprintf(stderr, "  beat edge total: %lld\n", total2);
    if (total2 <= m) {
      high = loseto;
    } else {
      low = loseto + 1;
    }

  }

  cout << (1+low) << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
