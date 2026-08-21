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








struct Entry {
  int idx;
  int x;
};
constexpr int INF = INT(1e9);
struct Query {
  int l;
  int r;
  int idx;
};


void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<Entry> entries(n);
  FORI(n)  entries[i] = {.idx = i, .x = a[i]};
  vector<Query> queries(q);
  FORI(q) {
    cin >> queries[i].l >> queries[i].r;
    queries[i].l--;
    queries[i].r--;
    queries[i].idx = i;
  }
  vector<bool> answers(q);

  sort(queries.begin(), queries.end(), [](const Query& q1, const Query& q2) {
    return q1.l < q2.l;
  });
  sort(entries.begin(), entries.end(), [](const Entry& e1, const Entry& e2) {
    return e1.x < e2.x;
  });
  vector<int> required_left(n, -INF);
  vector<int> required_right(n, INF);
  set<int> indices;
  // Go through ascending for required_right
  for (const auto entry : entries) {
    int idx = entry.idx;
    auto it = indices.lower_bound(idx);
    if (it != indices.end()) {
      required_right[idx] = *it;
    }  //otherwise INF
    indices.insert(idx);
  }
  // Go through descending for required_left
  indices.clear();
  reverse(entries.begin(), entries.end());
  for (const auto entry : entries) {
    int idx = entry.idx;
    auto it = indices.lower_bound(idx);
    if (it != indices.begin()) {
      required_left[idx] = *prev(it);
    }
    indices.insert(idx);
  }
  PRINTVEC(required_left);
  PRINTVEC(required_right);

  map<int, vector<int>> del_queue;
  for (int i = 0; i < n; i++) {
    if (required_left[i] != -INF) {
      del_queue[required_left[i]].pb(i);
    } else {
      required_right[i] = INF;  //basically marking it as invalid
    }
  }
  int logn = 0;
  while (exp(logn) < n+100)  logn++;
  auto min_combiner = [](int a, int b) { return min(a, b); };
  SegmentTree<int, decltype(min_combiner)> st(logn, min_combiner, INF, required_right);

  int qptr = 0;
  for (int i = 0; i < n; i++) {
    // process queries with left = i
    while (qptr < q && queries[qptr].l == i) {
      int achievable_r = st.range_query(i, queries[qptr].r);
      if (achievable_r <= queries[qptr].r) {
        // then the triple inversion exists and it is NOT perfect
        answers[queries[qptr].idx] = false;
      } else {
        answers[queries[qptr].idx] = true;
      }
      qptr++;
    }

    // process deletions for i as they are no longer valid now
    for (const int idx : del_queue[i]) {
      st.point_update(idx, INF);
    }
    assert(st.range_query(1, i) == INF);
  }

  for (int i = 0; i < q; i++) {
    cout << (answers[i] ? "YES" : "NO") << "\n";
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
