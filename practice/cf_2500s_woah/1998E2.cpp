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











struct Entry {
  long value;
  int index;
};
auto combiner = [](const Entry& e1, const Entry& e2) -> Entry {
  if (e1.value > e2.value)  return e1;
  return e2;
};
struct Tag {
  int val;
  bool start;  //false for stop
};


void solve_rec(int left, int right, const vector<long>& a, const vector<long>& a_prefix_sum, SegmentTree<Entry, decltype(combiner)>& rangemax,
    vector<vector<Tag>>& lessthan_tags, vector<vector<Tag>>& greaterthan_tags
    )
{
  assert(left <= right);
  if (left == right) {
    // no tags
    return;
  }
  Entry maxi = rangemax.range_query(left, right);
  int maxidx = maxi.index;
  // maxidx itself gets no more tags
  // left half
  {
    int l1 = left, r1 = maxidx-1;
    if (l1 <= r1) {
      long sum = a_prefix_sum[r1] - a_prefix_sum[l1-1];
      if (sum < maxi.value) {
        // we can't escape
        // then we will tag l1 to r1 with <= maxidx-1
        fprintf(stderr, "tagging %d...%d with <=%d\n", l1, r1, maxidx-1);
        lessthan_tags[l1].pb({maxidx-1, true});
        lessthan_tags[r1+1].pb({maxidx-1, false});
      }
      // otherwise there are no additional tags
      // recurse
      solve_rec(l1, r1, a, a_prefix_sum, rangemax, lessthan_tags, greaterthan_tags);
    }
  }
  // right half
  {
    int l2 = maxidx+1, r2 = right;
    if (l2 <= r2) {
      // find the minimum index i s.t. a[l2] + ... + a[i] >= a[maxidx]
      if (a_prefix_sum[r2] - a_prefix_sum[l2-1] < maxi.value) {
        // we can't escape
        // so all of these are imposs
        fprintf(stderr, "imposs: %d...%d", l2, r2, maxidx-1);
        lessthan_tags[l2].pb({0, true});
        lessthan_tags[r2+1].pb({0, false});
        greaterthan_tags[l2].pb({1, true});
        greaterthan_tags[r2+1].pb({1, false});
      } else {
        int blow = l2, bhigh = r2;
        while (blow < bhigh) {
          int bmid = (blow + bhigh) / 2;
          long sum = a_prefix_sum[bmid] - a_prefix_sum[l2-1];
          if (sum >= maxi.value) {
            bhigh = bmid;
          } else {
            blow = bmid + 1;
          }
        }
        fprintf(stderr, "tagging %d...%d with >=%d\n", l2, r2, blow);
        greaterthan_tags[l2].pb({blow, true});
        greaterthan_tags[r2+1].pb({blow, false});
        solve_rec(l2, r2, a, a_prefix_sum, rangemax, lessthan_tags, greaterthan_tags);
      }
    }
  }
}








void solve() {
  int n, _discard;
  cin >> n >> _discard;
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];
  vector<long> a_prefix_sum(n+1, 0);
  FORI1(n)  a_prefix_sum[i] = a_prefix_sum[i-1] + a[i];

  vector<Entry> init(n+1);
  FORI1(n)  init[i] = Entry{a[i], i};
  int logn = 0;  while (exp(logn) < n+10)  logn++;
  SegmentTree<Entry, decltype(combiner)> rangemax(logn, combiner, Entry{LONG(-1e18), -1}, init);

  vector<vector<Tag>> lessthan_tags(n+2);
  vector<vector<Tag>> greaterthan_tags(n+2);
  solve_rec(1, n, a, a_prefix_sum, rangemax, lessthan_tags, greaterthan_tags);

  multiset<int> active_less_tags;
  multiset<int> active_greater_tags;
  vector<long> final_diff_array(n+2, 0);
  for (int i = 1; i <= n; i++) {
    for (const Tag& tag : lessthan_tags[i]) {
      if (tag.start) {
        active_less_tags.insert(tag.val);
      } else {
        auto it = active_less_tags.find(tag.val);
        assert(it != active_less_tags.end());
        active_less_tags.erase(it);
      }
    }
    for (const Tag& tag : greaterthan_tags[i]) {
      if (tag.start) {
        active_greater_tags.insert(tag.val);
      } else {
        auto it = active_greater_tags.find(tag.val);
        assert(it != active_greater_tags.end());
        active_greater_tags.erase(it);
      }
    }

    int lowerbound = active_greater_tags.empty() ? 1 : *active_greater_tags.rbegin();
    lowerbound = max(lowerbound, i);
    int upperbound = active_less_tags.empty() ? n : *active_less_tags.begin();
    fprintf(stderr, "for i=%d, final range is %d ... %d\n", i, lowerbound, upperbound);
    if (lowerbound <= upperbound) {
      final_diff_array[lowerbound]++;
      final_diff_array[upperbound+1]--;
    }
  }

  long acc = 0;
  for (int i = 1; i <= n; i++) {
    acc += final_diff_array[i];
    cout << acc << " ";
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
