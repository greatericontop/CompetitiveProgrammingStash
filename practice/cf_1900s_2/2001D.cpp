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
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "true" : "false"); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
  #define PRINTVECB(...)
#endif
#define long int64_t
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
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









struct Entry {
  int num;
  int idx;
};


/*
 * Segment tree skeleton. Fill stuff in where appropriate.
 * Handwritten by me (might be slightly slow).
 */
#define exp(x) (1 << (x))
template <class T, class Combiner> class SegmentTree {
private:
  int max_layer;
  int n;
  vector<vector<T>> segments;  //segments[l] contains 0 to 2^l - 1
  Combiner combiner;
  T combine_empty;  //the identity/null element (e.g. 0 for sum, INT_MAX for min, etc.)

public:
  explicit SegmentTree(int max_layer, Combiner combiner, T combine_empty, const vector<T>& initialize)
      : max_layer(max_layer), n(exp(max_layer)), segments(max_layer + 1),
        combiner(combiner), combine_empty(combine_empty) {
    assert(initialize.size() <= n);
    segments[0] = initialize;  //this is a copy
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
    T answer_left = combine_empty;
    T answer_right = combine_empty;
    for (int layer = 0; layer <= max_layer; layer++) {
      if (left == right) {
        return combiner(combiner(answer_left, segments[layer][left]), answer_right);
      } else if (left == right + 1) {
        return combiner(answer_left, answer_right);
      }
      if (left % 2 == 1) {
        answer_left = combiner(answer_left, segments[layer][left]);
        left++;
      }
      if (right % 2 == 0) {
        answer_right = combiner(segments[layer][right], answer_right);
        right--;
      }
      left /= 2;
      right /= 2;
    }
    assert(false);
  }
};



void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  vector<int> unskippable_indices;
  vector<vector<int>> occurrences_of_num(n+1);
  for (int i = n-1; i >= 0; i--) {
    if (occurrences_of_num[a[i]].empty()) {
      unskippable_indices.pb(i);
    }
    occurrences_of_num[a[i]].pb(i);
  }
  auto take_min = [](const Entry& a, const Entry& b) -> Entry {
    if (a.num == b.num) {
      return (a.idx < b.idx) ? a : b;  //always return leftmost index
    } else {
      return (a.num < b.num) ? a : b;
    }
  };
  auto take_max = [](const Entry& a, const Entry& b) -> Entry {
    if (a.num == b.num) {
      return (a.idx < b.idx) ? a : b;  //always return leftmost index
    } else {
      return (a.num > b.num) ? a : b;
    }
  };
  Entry empty_min = {INT_MAX, INT_MAX};
  Entry empty_max = {INT_MIN, INT_MAX};
  int logn = 0;
  while (exp(logn) < n+20)  logn++;
  vector<Entry> initial_st(n);
  FORI(n)  initial_st[i] = {a[i], i};
  SegmentTree<Entry, decltype(take_min)> min_tree(logn, take_min, empty_min, initial_st);
  SegmentTree<Entry, decltype(take_max)> max_tree(logn, take_max, empty_max, initial_st);

  int cur = 0;
  bool next_is_max = true;
  vector<int> ans;
  vector<bool> already_taken(n+1, false);
  while (!unskippable_indices.empty()) {
    int next = unskippable_indices.back();
    if (already_taken[a[next]]) {
      unskippable_indices.pop_back();
      continue;
    }

    // range query between :cur: and :next:
    Entry e;
    if (next_is_max)  e = max_tree.range_query(cur, next);
    else  e = min_tree.range_query(cur, next);
    next_is_max = !next_is_max;
    ans.pb(e.num);
    already_taken[e.num] = true;
    cur = e.idx + 1;
    for (int i : occurrences_of_num[e.num]) {
      min_tree.point_update(i, empty_min);
      max_tree.point_update(i, empty_max);
    }
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << " ";
  }
  cout << "\n";
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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
