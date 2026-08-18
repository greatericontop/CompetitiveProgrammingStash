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








struct Person {
  int l;
  int r;
  int l_idx;
  int r_idx;
  int orig_i;
  int answer;
};



constexpr int RIGHT_END = 1'100'000'000;
void solve() {
  int n;
  cin >> n;
  vector<Person> a(n);
  vector<int> vals(2*n);
  FORI(n) {
    cin >> a[i].l >> a[i].r;
    vals[2*i] = a[i].l;
    vals[2*i+1] = a[i].r;
    a[i].orig_i = i;
  }
  sort(vals.begin(), vals.end());
  FORI(n) {
    a[i].l_idx = INT(lower_bound(vals.begin(), vals.end(), a[i].l) - vals.begin());
    assert(a[i].l_idx >= 0 && a[i].l_idx < 2*n);
    a[i].r_idx = INT(lower_bound(vals.begin(), vals.end(), a[i].r) - vals.begin());
    assert(a[i].r_idx >= 0 && a[i].r_idx < 2*n);
  }
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "cooridnate compressed person [%d %d] to [%d %d]\n", a[i].l, a[i].r, a[i].l_idx, a[i].r_idx);
  }

  int log2n = 0;
  while ((1 << log2n) < 2*n+100)  log2n++;
  auto rangemax = [](pairii a, pairii b) -> pairii {
    assert(a.first >= a.second && b.first >= b.second);
    int x = a.first, y = b.first;
    if (y > x)  swap(x, y);
    return {x, max(y, max(a.second, b.second))};
  };
  SegmentTree<pairii, decltype(rangemax)> segtree(log2n, rangemax, {INT_MIN, INT_MIN}, vector<pairii>(2*n, {INT_MIN, INT_MIN}));
  multiset<int> right_bounds;
  right_bounds.insert(RIGHT_END);

  sort(a.begin(), a.end(), [](const Person& p1, const Person& p2) {
    return p1.l < p2.l;
  });
  int action_ptr = 0;
  for (int query_ptr = 0; query_ptr < n; query_ptr++) {
    assert(action_ptr >= query_ptr);
    while (action_ptr < n && a[action_ptr].l == a[query_ptr].l) {
      right_bounds.insert(a[action_ptr].r);
      // segtree of left bound stored at right index
      pairii cur = segtree.range_query(a[action_ptr].r_idx, a[action_ptr].r_idx);
      segtree.point_update(a[action_ptr].r_idx, rangemax(cur, {a[action_ptr].l, INT_MIN}));
      action_ptr++;
    }

    int rightmost = *next(right_bounds.lower_bound(a[query_ptr].r));  //advance by 1 because not ourselves
    if (rightmost == RIGHT_END) {
      // there are no superset
      a[query_ptr].answer = 0;
    } else {
      pairii _q = segtree.range_query(a[query_ptr].r_idx, 2*n);
      fprintf(stderr, "  %d %d\n", _q.first, _q.second);
      int leftmost = segtree.range_query(a[query_ptr].r_idx, 2*n).second;  //again, second min, because not ourselves
      assert(leftmost != INT_MIN);
      int ans = rightmost - leftmost + 1 - (a[query_ptr].r - a[query_ptr].l + 1);
      fprintf(stderr, "for person [%d %d], feasible region is %d %d\n", a[query_ptr].l, a[query_ptr].r, leftmost, rightmost);
      assert(ans >= 0);
      a[query_ptr].answer = ans;
    }

  }

  vector<int> answers(n);
  FORI(n) {
    answers[a[i].orig_i] = a[i].answer;
  }
  FORI(n) {
    cout << answers[i] << "\n";
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
