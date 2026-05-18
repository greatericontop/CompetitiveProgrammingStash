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










struct User {
  int tp;
  int tc;
  int d;
};

constexpr static int MAX = 1'000'010;
constexpr static int INF = INT(1e8);

constexpr static inline int clamp(int x, int t, int d) {
  if (x < t)  return 0;
  return min(x, t+d);
}

void solve() {
  int n;
  cin >> n;
  vector<int> p(n);
  FORI(n)  cin >> p[i];
  vector<int> c(n);
  FORI(n)  cin >> c[i];
  int m;
  cin >> m;
  vector<User> queries(m);
  for (int i = 0; i < m; i++) {
    cin >> queries[i].tp;
  }
  for (int i = 0; i < m; i++) {
    cin >> queries[i].tc;
  }
  for (int i = 0; i < m; i++) {
    cin >> queries[i].d;
  }

  // Keyed by pi, min ci for each pi
  vector<int> min_c(MAX, INF);
  // Keyed by ci, min pi for each ci
  vector<int> min_p(MAX, INF);
  // Keyed by pi, min ci+pi for each pi
  vector<int> min_cp(MAX, INF);
  for (int i = 0; i < n; i++) {
    min_c[p[i]] = min(min_c[p[i]], c[i]);
    min_p[c[i]] = min(min_p[c[i]], p[i]);
    min_cp[p[i]] = min(min_cp[p[i]], c[i] + p[i]);
  }

  auto min_combiner = [](int a, int b) { return min(a, b); };
  SegmentTree<int, decltype(min_combiner)> min_c_st(20, min_combiner, INF, min_c);
  SegmentTree<int, decltype(min_combiner)> min_p_st(20, min_combiner, INF, min_p);
  SegmentTree<int, decltype(min_combiner)> min_cp_st(20, min_combiner, INF, min_cp);


  for (const auto& query : queries) {
    int ans = INF;

    // p < tp, find minimum c
    int p0_minc = min_c_st.range_query(0, max(0, query.tp - 1));
    if (p0_minc != INF) {
      int p0_ans = 0 + clamp(p0_minc, query.tc, query.d);
      ans = min(ans, p0_ans);
      fprintf(stderr, "p0 ans = %d\n", p0_ans);
    }
    // p >= tp+d, find minimum c
    int pmax_minc = min_c_st.range_query(min(query.tp + query.d, MAX-1), MAX-1);
    if (pmax_minc != INF) {
      int pmax_ans = (query.tp + query.d) + clamp(pmax_minc, query.tc, query.d);
      ans = min(ans, pmax_ans);
      fprintf(stderr, "pmax ans = %d\n", pmax_ans);
    }

    // c < tc, find minimum p
    int c0_minp = min_p_st.range_query(0, max(0, query.tc - 1));
    if (c0_minp != INF) {
      int c0_ans = 0 + clamp(c0_minp, query.tp, query.d);
      ans = min(ans, c0_ans);
      fprintf(stderr, "c0 ans = %d\n", c0_ans);
    }
    // c >= tc+d, find minimum p
    int cmax_minp = min_p_st.range_query(min(query.tc + query.d, MAX-1), MAX-1);
    if (cmax_minp != INF) {
      int cmax_ans = (query.tc + query.d) + clamp(cmax_minp, query.tp, query.d);
      ans = min(ans, cmax_ans);
      fprintf(stderr, "cmax ans = %d\n", cmax_ans);
    }

    // Middle: query tp <= p <= tp+d
    // this number may overshoot but no loss of correctness
    int middle_min_cp = min_cp_st.range_query(query.tp, min(query.tp + query.d, MAX-1));
    ans = min(ans, middle_min_cp);
    fprintf(stderr, "middle ans = %d\n", middle_min_cp);

    assert(ans != INF);
    cout << ans << "\n";
  }



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
