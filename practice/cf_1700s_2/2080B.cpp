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










void solve() {
  int n, m;
  long x;
  cin >> n >> m >> x;
  vector<long> a(n+1); a[0] = 0;
  for (int i = 1; i <= n; i++)  cin >> a[i];
  vector<long> a_prefix_sum(n+1); a_prefix_sum[0] = 0;
  for (int i = 1; i <= n; i++)  a_prefix_sum[i] = a_prefix_sum[i-1] + a[i];
  vector<int> b(m);
  for (int i = 0; i < m; i++)  cin >> b[i];
  sort(b.begin(), b.end());

  long best_score = -1;
  for (int i = 1; i <= n; i++) {
    // Track a[i] will be the track we want

    // runner to the right of us
    auto it = lower_bound(b.begin(), b.end(), i);
    if (it != b.end()) {
      int j = *it;
      long time_waste = a_prefix_sum[j] - a_prefix_sum[i];
      if (x >= time_waste) {
        long ai_score = (x - time_waste) / a[i];
        fprintf(stderr, "score with track %d, runner at %d:  %lld\n", i, j, ai_score + (j-i));
        best_score = max(best_score, ai_score + (j-i));
      }
    }

    if (it != b.begin()) {
      int j = *(prev(it));
      long time_waste = a_prefix_sum[i-1] - a_prefix_sum[j-1];
      if (x >= time_waste) {
        long ai_score = (x - time_waste) / a[i];
        fprintf(stderr, "score with track %d, runner at %d:  %lld\n", i, j, ai_score + (i-j));
        best_score = max(best_score, ai_score + (i-j));
      }
    }

  }

  cout << best_score << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
