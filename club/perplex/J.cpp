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
constexpr static long MOD =   998'244'353LL;
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
/* O(log exp) */
int64_t mod_exp(int64_t base, int64_t exp) {
  int64_t result = 1;
  while (exp > 0) {
    if (exp & 1)  result = (result * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

/* Only works for primes, O(log MOD) */
int64_t modular_inverse(int64_t a) {
  return mod_exp(a, MOD - 2);
}










void solve() {
  string s;  cin >> s;  int n = s.size();
  int q;  cin >> q;

  vector<long> powersof2(n+10, 1);
  for (int i = 1; i <= n+9; i++) {
    powersof2[i] = (2 * powersof2[i-1]) % MOD;
  }


  auto add_combiner = [](long a, long b) -> long {
    return (a + b) % MOD;
  };
  int logn = 1;  while (exp(logn) < n+20)  logn++;
  SegmentTree<long, decltype(add_combiner)> leftzero(logn, add_combiner, 0, vector<long>(n, 0));
  SegmentTree<long, decltype(add_combiner)> rightzero(logn, add_combiner, 0, vector<long>(n, 0));
  SegmentTree<long, decltype(add_combiner)> leftone(logn, add_combiner, 0, vector<long>(n, 0));
  SegmentTree<long, decltype(add_combiner)> rightone(logn, add_combiner, 0, vector<long>(n, 0));

  long sum = 0;

  auto calc_contrib = [&](SegmentTree<long, decltype(add_combiner)>& l, SegmentTree<long, decltype(add_combiner)>& r, int i) -> long {
    long leftmultiplier = powersof2[n-1-i];
    long left_contrib = l.range_query(0, i-1);
    long rightmultiplier = powersof2[i];
    long right_contrib = r.range_query(i+1, n);
    fprintf(stderr, "calc_contrib: leftmultiplier=%ld, left_contrib=%ld, rightmultiplier=%ld, right_contrib=%ld\n", leftmultiplier, left_contrib, rightmultiplier, right_contrib);
    return (leftmultiplier * left_contrib + rightmultiplier * right_contrib) % MOD;
  };
  auto place = [&](SegmentTree<long, decltype(add_combiner)>& l, SegmentTree<long, decltype(add_combiner)>& r, int i) -> void {
    // place in left with value 2^i
    l.point_update(i, powersof2[i]);
    // place in right
    r.point_update(i, powersof2[n-1-i]);
    sum += calc_contrib(l, r, i);
    fprintf(stderr, "contrib was %ld\n", calc_contrib(l, r, i));
    sum %= MOD;
  };
  auto delet = [&](SegmentTree<long, decltype(add_combiner)>& l, SegmentTree<long, decltype(add_combiner)>& r, int i) -> void {
    sum -= calc_contrib(l, r, i);
    sum += MOD;
    sum %= MOD;
    l.point_update(i, 0);
    r.point_update(i, 0);
  };

  for (int i = 0; i < n; i++) {
    if (s[i] == '0') {
      place(leftzero, rightzero, i);
    } else {
      place(leftone, rightone, i);
    }
  }

  // calc total
  long total = 0;
  long choose = 1;
  //subseqs of length i
  for (int i = 1; i <= n; i++) {
    choose *= (n+1-i);
    choose %= MOD;
    choose *= modular_inverse(i);
    choose %= MOD;

    total += choose * i;
    total %= MOD;
  }
  fprintf(stderr, "total %ld\n", total);


  while (q --> 0) {
    int i;  cin >> i;  i--;

    if (s[i] == '0') {
      // erase zero, place one
      s[i] = '1';
      delet(leftzero, rightzero, i);
      place(leftone, rightone, i);
    } else {
      s[i] = '0';
      delet(leftone, rightone, i);
      place(leftzero, rightzero, i);
    }

    long ans = total - sum + MOD;
    ans %= MOD;
    cout << ans << " ";
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
