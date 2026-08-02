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









struct Segment {
  int l;
  int r;
  int idx;

  // to be filled in later
  int answer_subset;
};

struct Event {
  int x;
  int idx;
  char type; // `S`tart, `E`nd
};


void solve() {
  int n, m;
  cin >> n >> m;
  vector<Segment> segments(n);
  FORI(n) {
    cin >> segments[i].l >> segments[i].r;
    segments[i].idx = i;
  }
  Segment leftmost = segments[0];
  Segment rightmost = segments[0];
  for (const auto& seg : segments) {
    if (seg.r < leftmost.r) {
      leftmost = seg;
    }
    if (seg.l > rightmost.l) {
      rightmost = seg;
    }
  }

  vector<Event> events;
  vector<int> coord_compress;
  coord_compress.pb(-1);
  coord_compress.pb(INT(1e9+10));
  for (const auto& seg : segments) {
    coord_compress.pb(seg.l);
    coord_compress.pb(seg.r);
    events.pb({seg.l, seg.idx, 'S'});
    events.pb({seg.r+1, seg.idx, 'E'});
  }
  sort(coord_compress.begin(), coord_compress.end());
  sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
    return a.x < b.x;
  });
  int logn = 1;
  while (exp(logn) < coord_compress.size()+20)  logn++;
  auto min_combiner = [](int a, int b) { return min(a, b); };
  SegmentTree<int, decltype(min_combiner)> segtree(logn, min_combiner, INT(1e9+10), vector<int>(exp(logn), INT(1e9+10)));

  // Now do segtree
  // A closed (L, R both past) segment has its size placed at L
  // Then RMQ from L to R of the current segment that just closed
  int action_ptr = 0;
  for (int query_ptr = 0; query_ptr < events.size(); query_ptr++) {
    assert(action_ptr >= query_ptr);
    while (action_ptr < events.size() && events[action_ptr].x == events[query_ptr].x) {
      Event ev = events[action_ptr];
      if (ev.type == 'E') {
        int l_coordinate_compressed = lower_bound(coord_compress.begin(), coord_compress.end(), segments[ev.idx].l) - coord_compress.begin();
        int old_val = segtree.range_query(l_coordinate_compressed, l_coordinate_compressed);
        int new_val = min(old_val, segments[ev.idx].r - segments[ev.idx].l + 1);
        segtree.point_update(l_coordinate_compressed, new_val);
      }
      action_ptr++;
    }

    Event ev = events[query_ptr];
    if (ev.type == 'E') {
      int l_coordinate_compressed = lower_bound(coord_compress.begin(), coord_compress.end(), segments[ev.idx].l) - coord_compress.begin();
      int min_size = segtree.range_query(l_coordinate_compressed, coord_compress.size()+10);
      segments[ev.idx].answer_subset = min_size;
    }
  }

  int max_diff = 0;
  for (const auto& seg : segments) {
    // find size of minimum
    int minimum_size = seg.answer_subset;
    int left_size = max(leftmost.r - seg.l + 1, 0);
    int right_size = max(seg.r - rightmost.l + 1, 0);
    minimum_size = min(minimum_size, min(left_size, right_size));
    int our_size = seg.r - seg.l + 1;
    int diff = our_size - (2*minimum_size - our_size);
    max_diff = max(max_diff, diff);
  }

  cout << max_diff << "\n";





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
