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









long find_first_multiplier_ge(long x, long a, long b, long m) {
  long l = 0, r = a+b;
  while (l < r) {
    long multiplier = l + (r-l)/2;

    long total = multiplier * x - max(0LL, multiplier - b);

    if (total >= m) {
      r = multiplier;
    } else {
      l = multiplier + 1;
    }
  }
  return l;
}

void solve() {
  int n; long m;
  cin >> n >> m;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<int> c(n);
  FORI(n)  cin >> c[i];
  map<int, long> counts;
  FORI(n)  counts[a[i]] = c[i];

  long best = -100;

  map<int, long> counts_frozen = counts;
  for (auto& [v, counta] : counts_frozen) {
    long countb = counts[v+1];
    if (countb == 0) {
      long score = v * min(m / v, counta);
      fprintf(stderr, "[%d x%lld]: score %lld\n", v, counta, score);
      best = max(best, score);
    } else {
      long x = v+1;
      long multiplier = find_first_multiplier_ge(x, counta, countb, m);
      long lower_bound_score = multiplier*x - min(counta, multiplier);
      if (lower_bound_score <= m) {
        long upper_bound_score = multiplier*x - max(0LL, multiplier - countb);
        long new_score = min(m, upper_bound_score);
        fprintf(stderr, "[%d x%lld]: full multiplier %lld, score = %lld\n", v, counta, multiplier, new_score);
        best = max(best, new_score);
      } else {
        multiplier--;
        long score = multiplier*x - max(0LL, multiplier - countb);
        fprintf(stderr, "[%d x%lld]: partial multiplier %lld, score %lld\n", v, counta, multiplier, score);
        best = max(best, score);
      }

    }

  }


  cout << best << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
