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
template <class T> class Fenwick {
private:
  int n;
  vector<T> data; // note: 1-indexed

public:
  explicit Fenwick(int n) : n(n), data(n+1) {
  }

  /* Initialize from an array of values[1...n] (it's 1-indexed!) */
  void init(vector<T> values) {
    vector<T> prefix_sums(n+1);
    prefix_sums[0] = 0;
    for (int i = 1; i <= n; i++) {
      prefix_sums[i] = prefix_sums[i-1] + values[i];
    }
    for (int i = 1; i <= n; i++) {
      data[i] = prefix_sums[i] - prefix_sums[i - (i & -i)];
    }
  }

  void add(int i, T value) {
    while (i <= n) {
      data[i] += value;
      i += i & -i;
    }
  }

  void set(int i, T value) {
    T current_value = prefix_sum(i) - prefix_sum(i-1);
    add(i, value - current_value);
  }

  /* Prefix sum from indices 1 to i inclusive */
  T prefix_sum(int i) {
    if (i == 0)  return 0;
    T sum = 0;
    while (i >= 1) {
      sum += data[i];
      i -= i & -i;
    }
    return sum;
  }

  /* Range sum from left to right inclusive */
  T range_sum(int left, int right) {
    return prefix_sum(right) - prefix_sum(left-1);
  }

};





struct Segment {
  int l;
  int r;
  int idx;
  int fenwick_idx;
};


constexpr static long INF = 5e18;

void solve() {
  int n;
  long k;
  cin >> n >> k;
  vector<Segment> segments(n);
  FORI(n) {
    cin >> segments[i].l;
    segments[i].idx = i;
  }
  FORI(n) {
    cin >> segments[i].r;
  }
  sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b) {
    return a.r < b.r;
  });
  FORI(n) {
    segments[i].fenwick_idx = i+2;
  }
  sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b) {
    return a.idx < b.idx;
  });

  Fenwick<long> fen(n+10);
  Fenwick<int> fen_count(n+10);
  fen.init(vector<long>(n+20, 0));
  fen_count.init(vector<int>(n+20, 0));
  long total_sum = 0;
  long best_cost = INF;
  for (int i = 0; i < n; i++) {
    Segment s = segments[i];
    long this_seg_size = s.r - s.l + 1;
    long max_loss = total_sum - k + this_seg_size;
    fprintf(stderr, "max loss from existing: %ld (k=%ld)\n", max_loss, k);
    if (max_loss < 0) {
      total_sum += this_seg_size;
      if (s.l == s.r) {
        // only discard size 1 segs
        assert(fen.range_sum(s.fenwick_idx, s.fenwick_idx) == 0);  //this slot should be empty
        fen.add(s.fenwick_idx, this_seg_size);
        fen_count.add(s.fenwick_idx, 1);
      }
      continue;
    } else {
      // can remove up to max_loss while remaining >= k-this_seg_size (and then we will add ourselves at the end)
      int l = 1, r = n+5;
      while (l < r) {
        int mid = l + (r-l+1)/2;
        long sum = fen.prefix_sum(mid);
        if (sum <= max_loss) {
          l = mid;
        } else {
          r = mid-1;
        }
      }
      int segs_saved = fen_count.prefix_sum(l);
      long required_in_our_seg = max<long>(this_seg_size - (max_loss - fen.prefix_sum(l)), 1);
      long final_x = s.l + required_in_our_seg - 1;
      int segs_used = i+1 - segs_saved;
      long cost = final_x + 2*LONG(segs_used);
      best_cost = min(best_cost, cost);
      fprintf(stderr, "Debug: #%d, saved %d segs, required in our seg %ld, final x %ld, cost %ld\n", i, segs_saved, required_in_our_seg, final_x, cost);
    }

    total_sum += this_seg_size;
    if (s.l == s.r) {
      // only discard size 1 segs
      assert(fen.range_sum(s.fenwick_idx, s.fenwick_idx) == 0);  //this slot should be empty
      fen.add(s.fenwick_idx, this_seg_size);
      fen_count.add(s.fenwick_idx, 1);
    }
  }

  if (best_cost == INF)  best_cost = -1;
  cout << best_cost << "\n";


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
