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
    T answer = combine_empty;
    while (left <= right) {
      // Find biggest interval (aka what's the biggest power of 2 that divides a)
      int layer_i = left;
      int layer = 0;
      while ((left % (2 << layer) == 0) && (layer < max_layer) && (left + (2 << layer) - 1 <= right)) {
        layer++;
        layer_i /= 2;
      }
      answer = combiner(answer, segments[layer][layer_i]);  //order matters here
      left += exp(layer);
    }
    return answer;
  }
};








struct Segment {
  // Base loss (summed over all inside) if 0 input.
  // Every 1 input reduces base loss by 1, until base loss is 0. Further input goes directly to output.
  long base_loss;
  // Base output. Fed as input to the next segment, or discarded.
  long base_output;

  void print() const {
    fprintf(stderr, "{loss%lld output=%lld}", base_loss, base_output);
  }
};

auto combine_segment = [](const Segment& l, const Segment& r) -> Segment {
  //l.print(); fprintf(stderr, "  +  "); r.print(); fprintf(stderr, "\n");
  long input_to_r = l.base_output;

  long new_r_loss = max(0LL, r.base_loss - input_to_r);
  fprintf(stderr, "  new right loss: %lld\n", new_r_loss);
  long input_spent = r.base_loss - new_r_loss;
  assert(input_spent <= r.base_loss);
  assert(input_spent < r.base_loss || new_r_loss == 0);
  long new_r_output = r.base_output + (input_to_r - input_spent);

  return Segment{l.base_loss + new_r_loss, new_r_output};
};




void solve() {
  int n, q;
  cin >> n >> q;
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];
  vector<long> b(n+1);
  FORI1(n)  cin >> b[i];
  long _c_discard;
  FORI(n-1)  cin >> _c_discard;

  long sum_b = 0LL;
  vector<Segment> init(n+1);
  FORI1(n) {
    long base_loss = max(0LL, b[i] - a[i]);
    long base_output = max(0LL, a[i] - b[i]);
    init[i] = Segment{base_loss, base_output};
    sum_b += b[i];
  }

  int logn = 0;
  while (exp(logn) < n+5)  logn++;
  SegmentTree<Segment, decltype(combine_segment)> segtree(logn, combine_segment, Segment{0LL, 0LL}, init);

  while (q --> 0) {
    int p; long x, y;
    cin >> p >> x >> y >> _c_discard;

    sum_b -= b[p];
    segtree.point_update(p, Segment{max(0LL, y - x), max(0LL, x - y)});
    a[p] = x;
    b[p] = y;
    sum_b += b[p];

    Segment s = segtree.range_query(1, n);
    long total_loss = s.base_loss;
    cout << sum_b - total_loss << "\n";


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
