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









bool can_get(int target_rating, int n, const vector<int>& a) {
  fprintf(stderr, "try goal %d\n", target_rating);
  // your rating after performing contest [i]
  vector<int> prefix_ratings(n+1);
  prefix_ratings[0] = 0;
  for (int i = 1; i <= n; i++) {
    int cur = prefix_ratings[i-1];
    int delta = (a[i] > cur) ? 1 : ((a[i] < cur) ? -1 : 0);
    prefix_ratings[i] = cur + delta;
  }
  PRINTVEC(prefix_ratings);
  // the rating required right after contest [i] to be able to finish with >= target_rating
  vector<int> suffix_requirements(n+1);
  suffix_requirements[n] = target_rating;
  for (int i = n; i >= 1; i--) {
    if (a[i] >= suffix_requirements[i]) {
      suffix_requirements[i-1] = suffix_requirements[i] - 1;
    } else {
      suffix_requirements[i-1] = suffix_requirements[i] + 1;
    }
  }
  PRINTVEC(suffix_requirements);
  vector<int> suffix_min(n+1);
  suffix_min[n] = suffix_requirements[n];
  for (int i = n-1; i >= 0; i--) {
    suffix_min[i] = min(suffix_min[i+1], suffix_requirements[i]);
  }

  // Take the first i contests
  for (int i = 0; i <= n-1; i++) {
    int rating_after = prefix_ratings[i];
    // can jump to after i+1 ... after n
    int req = suffix_min[i+1];
    if (rating_after >= req) {
      fprintf(stderr, "  OK\n");
      return true;
    }
  }
  fprintf(stderr, "  impossible\n");
  return false;
}


void solve() {
  int n;
  cin >> n;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];

  // BSTA on max rating you can get
  int l = 0, r = n;
  while (l < r) {
    int m = l + (r-l+1)/2;
    if (can_get(m, n, a)) {
      l = m;
    } else {
      r = m - 1;
    }
  }

  cout << l << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
