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
  explicit SegmentTree(int max_layer, Combiner combiner, T combine_empty, const vector<T>&& initialize)
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








/*
 * Return sum of blocked indices if each subarray can sum to at most :limit:
 */
long calc(int n, const vector<long>& a, long limit) {
  fprintf(stderr, "calculate sum of blocked indices for limit %ld\n", limit);
  vector<long> prefix_sum(n+1, 0);
  for (int i = 1; i <= n; i++)  prefix_sum[i] = prefix_sum[i-1] + a[i];
  vector<int> earliest(n+2, -1);
  // two pointers
  {
    int i = n;
    for (int j = n+1; j >= 0; j--) {
      // want highest i s.t. prefix_sum[j-1] - prefix_sum[i] <= limit, so then dp[j] reaches back to i
      while (i > 0 && prefix_sum[j - 1] - prefix_sum[i - 1] <= limit)  i--;
      earliest[j] = i;
    }
  }
  PRINTVEC(earliest);

  // now run dp
  int logn = 0;
  while (exp(logn) < n+10)  logn++;
  auto comb = [](long x, long y) { return min(x, y); };
  SegmentTree<long, decltype(comb)> dp(logn, comb, LONG(1e18), vector<long>(n+1, 0));

  for (int i = 1; i <= n; i++) {
    long best = dp.range_query(earliest[i], i-1);
    dp.point_update(i, best + a[i]);
    fprintf(stderr, "  dp[%d] <- %ld\n", i, best + a[i]);
  }

  long ret = dp.range_query(earliest[n+1], n);
  fprintf(stderr, "  return %ld (querying %d<->%d)\n", ret, earliest[n+1], n);
  return ret;
}






void solve() {
  int n;
  cin >> n;
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];

  // find the lowest index where (max subarray) >= (blocked sum)
  long l = 0, r = LONG(1e14);
  while (l < r) {
    long mid = l + (r-l)/2;
    long blocked_sum = calc(n, a, mid);
    if (mid >= blocked_sum) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  long ans = LONG(1e18);
  ans = min(ans, max(l, calc(n, a, l)));
  if (l >= 1) {
    // l-1 would be on the other side
    ans = min(ans, max((l-1), calc(n, a, l-1)));
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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
