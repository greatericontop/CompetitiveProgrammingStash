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
/*
 * Segment tree skeleton. Fill stuff in where appropriate.
 * Handwritten by me (might be slightly slow).
 */
#define exp(x) (1 << (x))
template <class T, class Combiner> class SegmentTree {
private:
  int max_layer;
  int n;
  vector<vector<T>> segments; // segments[l] contains 0 to 2^l - 1
  Combiner combiner;
  T combine_empty; // the identity/null element (e.g. 0 for sum, INT_MAX for min, etc.)

public:
  explicit SegmentTree(int max_layer, Combiner combiner, T combine_empty, const vector<T>& initialize)
      : max_layer(max_layer), n(exp(max_layer)), segments(max_layer + 1),
      combiner(combiner), combine_empty(combine_empty) {
    assert(initialize.size() <= n);
    segments[0] = initialize;
    while (segments[0].size() < n)  segments[0].push_back(combine_empty);

    for (int layer = 1; layer <= max_layer; layer++) {
      for (int i = 0; i < exp(max_layer-layer); i++) {
        segments[layer].push_back(combiner(segments[layer-1][2*i], segments[layer-1][2*i+1]));
      }
    }
  }

  void point_update(int i, T new_value) {
    segments[0][i] = new_value;
    for (int layer = 1; layer <= max_layer; layer++) {
      i /= 2;
      segments[layer][i] = combiner(segments[layer-1][2*i], segments[layer-1][2*i+1]);
    }
  }

  /* Range query left to right inclusive, 0-indexed */
  T range_query(int left, int right) {
    T answer = combine_empty;
    while (left <= right) {
      // Find biggest interval (aka what's the biggest power of 2 that divides a)
      int layer_i = left;
      int layer = 0;
      while ((left % (2 << layer) == 0) && (layer < 18) && (left + (2 << layer) - 1 <= right)) {
        layer++;
        layer_i /= 2;
      }
      answer = combiner(answer, segments[layer][layer_i]);
      left += exp(layer);
    }
    return answer;
  }
};

constexpr static inline long lcm(long a, long b) {
  return (a / gcd(a, b)) * b;
}









void solve() {
  int n;
  cin >> n;
  vector<long> a(n);
  vector<long> b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }
  vector<long> atimesb(n);
  FORI(n)  atimesb[i] = a[i] * b[i];
  int logn = 1;
  while (exp(logn) < n+100)  logn++;
  SegmentTree<long, function<long(long, long)>> lcm_segment(logn, [](long x, long y) { return lcm(x, y); }, 1L, b);
  SegmentTree<long, function<long(long, long)>> gcd_segment(logn, [](long x, long y) { return gcd(x, y); }, 0L, atimesb);

  vector<int> intervals(n);
  long total_lcm = lcm_segment.range_query(0, 0);
  long total_gcd = gcd_segment.range_query(0, 0);
  int j = 0;
  for (int i = 0; i < n; i++) {
    while (j < n-1) {
      long next_lcm = lcm(total_lcm, b[j+1]);
      long next_gcd = gcd(total_gcd, atimesb[j+1]);
      fprintf(stderr, "i=%d j=%d  lcm %lld gcd %lld\n", i, j, next_lcm, next_gcd);
      if (next_gcd % next_lcm == 0) {
        total_lcm = next_lcm;
        total_gcd = next_gcd;
        j++;
      } else {
        // found last one
        break;
      }
    }
    intervals[i] = j;
    assert(j >= i);
    if (j == i)  j = i+1;
    total_lcm = lcm_segment.range_query(i+1, j);
    total_gcd = gcd_segment.range_query(i+1, j);
  }

  PRINTVEC(intervals);

  // Hi Kent
  // dp[i] = min number of price tags for 0...i
  vector<int> dp(n, 1e9);
  for (int i = -1; i < n-1; i++) {
    int j = intervals[i+1];
    int dpi = i == -1 ? 0 : dp[i];
    dp[j] = min(dp[j], dpi + 1);
  }
  PRINTVEC(dp);

  cout << dp[n-1] << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
