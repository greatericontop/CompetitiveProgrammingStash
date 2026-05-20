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
  T range_query(int left, int right) const {
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










auto comb = [](const pairii& a, const pairii& b) {
    return pairii(min(a.first, b.first), max(a.second, b.second));
};


struct Interval {
  int l;
  int r;


  bool is_valid(const SegmentTree<pairii, decltype(comb)>& segtree) const {
    auto p = segtree.range_query(l, r);
    return (p.first == l) && (p.second == r);
  }

  bool operator<(const Interval& other) const {
    return r < other.r;
  }
};


void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> p(n+1);
  for (int i = 1; i <= n; i++)  cin >> p[i];
  string s1; cin >> s1;
  string s = " " + s1;


  int logn = 1;
  while (exp(logn) < n+20)  logn++;
  vector<pairii> init(n+1);
  for (int i = 1; i <= n; i++) {
    init[i] = {p[i], p[i]};
  }
  SegmentTree<pairii, decltype(comb)> segtree(logn, comb, {INT_MAX, INT_MIN}, init);

  int num_invalid_intervals = 0;
  set<Interval> intervals;
  // initial assignment of intervals
  int start = 1;
  for (int i = 2; i <= n; i++) {
    if (s[i] == 'R' && s[i-1] == 'L') {
      Interval new_interval{start, i-1};
      if (!new_interval.is_valid(segtree))  num_invalid_intervals++;
      intervals.insert(new_interval);
      start = i;
    }
    if (i == n) {
      Interval new_interval{start, n};
      if (!new_interval.is_valid(segtree))  num_invalid_intervals++;
      intervals.insert(new_interval);
    }
  }

  fprintf(stderr, "initial list of intervals:\n");
  for (const auto& interval : intervals) {
    fprintf(stderr, "  [%d, %d] (valid: %d)\n", interval.l, interval.r, interval.is_valid(segtree));
  }

  while (q --> 0) {
    // flip s[i]
    int i; cin >> i;
    fprintf(stderr, "query i = %d\n", i);
    s[i] = (s[i] == 'L' ? 'R' : 'L');
    auto it = intervals.lower_bound(Interval{i, i});  //interval that contains us
    assert(it != intervals.end());
    int l = it->l, r = it->r;
    set<int> interesting_indices;
    interesting_indices.insert(i); interesting_indices.insert(i+1);
    if (it != intervals.begin()) {
      auto it1 = prev(it);
      l = it1->l;
      interesting_indices.insert(it1->r+1);
      if (!(it1->is_valid(segtree)))  num_invalid_intervals--;
      intervals.erase(it1);
    }
    if (next(it) != intervals.end()) {
      auto it2 = next(it);
      r = it2->r;
      interesting_indices.insert(it2->l);
      if (!(it2->is_valid(segtree)))  num_invalid_intervals--;
      intervals.erase(it2);
    }
    if (!(it->is_valid(segtree)))  num_invalid_intervals--;
    intervals.erase(it);
    interesting_indices.erase(1); interesting_indices.erase(n+1);
    interesting_indices.insert(r+1);

    // rebuild
    fprintf(stderr, "rebuilding: l=%d, r=%d\n", l, r);
    PRINTVEC(interesting_indices);
    int start1 = l;
    for (int j : interesting_indices) {
      if (j == r+1) {
        Interval new_interval{start1, j-1};
        assert(j == n+1 || (s[j] == 'R' && s[j-1] == 'L'));
        if (!new_interval.is_valid(segtree))  num_invalid_intervals++;
        intervals.insert(new_interval);
      } else if (s[j] == 'R' && s[j-1] == 'L') {
        Interval new_interval{start1, j-1};
        if (!new_interval.is_valid(segtree))  num_invalid_intervals++;
        intervals.insert(new_interval);
        start1 = j;
      }
    }

    fprintf(stderr, "intervals after query:\n");
    for (const auto& interval : intervals) {
      fprintf(stderr, "  [%d, %d] (valid: %d)\n", interval.l, interval.r, interval.is_valid(segtree));
    }

    if (num_invalid_intervals > 0) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }

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
