#include <bits/stdc++.h>
using namespace std;


/*I FULLY EXPECT THIS TO TLE*/


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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;
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
  explicit SegmentTree(int max_layer, Combiner combiner, T combine_empty, const vector<T>&& initialize)
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








auto add_combiner = [](int a, int b) { return a + b; };

//13 log n...
long evaluate(int n, const set<int> sets[5], vector<SegmentTree<int, decltype(add_combiner)>>& segment_trees) {
  int d_mask = *sets[4].rbegin();
  int c_mask = max(d_mask, *sets[3].rbegin());
  int b_mask = max(c_mask, *sets[2].rbegin());
  int a_mask = max(b_mask, *sets[1].rbegin());
  long answer = 0;
  int count_a_less = (a_mask == -1) ? 0 : segment_trees[0].range_query(0, a_mask-1);
  int count_a_more = segment_trees[0].range_query(a_mask+1, n-1);
  int count_b_less = (b_mask == -1) ? 0 : segment_trees[1].range_query(0, b_mask-1);
  int count_b_more = segment_trees[1].range_query(b_mask+1, n-1);
  int count_c_less = (c_mask == -1) ? 0 : segment_trees[2].range_query(0, c_mask-1);
  int count_c_more = segment_trees[2].range_query(c_mask+1, n-1);
  int count_d_less = (d_mask == -1) ? 0 : segment_trees[3].range_query(0, d_mask-1);
  int count_d_more = segment_trees[3].range_query(d_mask+1, n-1);
  int count_e = segment_trees[4].range_query(0, n-1);
  return LONG(count_a_more - count_a_less) + 10LL*LONG(count_b_more - count_b_less)
      + 100LL*LONG(count_c_more - count_c_less) + 1000LL*LONG(count_d_more - count_d_less) + 10000LL*LONG(count_e);
}


void solve() {
  string s;
  cin >> s;
  int n = s.size();
  int logn = 1;
  while (exp(logn) < n+10)  logn++;
  set<int> sets[5];
  for (int i = 0; i < 5; i++)  sets[i].insert(-1);
  vector<SegmentTree<int, decltype(add_combiner)>> segment_trees(5, SegmentTree(logn, add_combiner, 0, vector<int>(n, 0)));

  for (int i = 0; i < n; i++) {
    int idx = s[i] - 'A';
    assert(idx >= 0 && idx <= 4);
    sets[idx].insert(i);
    segment_trees[idx].point_update(i, 1);
  }

  long ans = evaluate(n, sets, segment_trees);
  // 1 million * 13*18 = questionable...
  for (int i = 0; i < n; i++) {
    int old_idx = s[i] - 'A';
    sets[old_idx].erase(i);
    segment_trees[old_idx].point_update(i, 0);
    for (int new_idx = 0; new_idx < 5; new_idx++) {
      if (new_idx == old_idx)  continue;
      sets[new_idx].insert(i);
      segment_trees[new_idx].point_update(i, 1);
      long ev = evaluate(n, sets, segment_trees);
      fprintf(stderr, "index %d [%c -> %c] ev: %lld\n", i, 'A'+old_idx, 'A'+new_idx, ev);
      ans = max(ans, ev);
      sets[new_idx].erase(i);
      segment_trees[new_idx].point_update(i, 0);
    }
    sets[old_idx].insert(i);
    segment_trees[old_idx].point_update(i, 1);
  }

  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
