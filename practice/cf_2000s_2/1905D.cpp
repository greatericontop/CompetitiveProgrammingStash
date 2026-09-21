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



struct StackEntry {
  int idx;
  int val;
};
struct Sc3developerLazyDataStructure {
  int n;
  vector<int> original_a;  //1-index
  vector<long> prefix_sum;
  int offset;
  vector<StackEntry> ends;
  long lazy_stack_sum;

  void push(int i) {
    // push StackEntry{ i, n (+ offset) }
    // delete all entries >= us
    while (!ends.empty() && ends.back().idx >= i) {
      int elts = n + 1 - ends.back().idx;
      lazy_stack_sum -= LONG(elts) * LONG(ends.back().val);
      ends.pop_back();
      if (!ends.empty()) {
        // since the previous stack frame now takes over
        lazy_stack_sum += LONG(elts) * LONG(ends.back().val);
      }
    }
    // new stack frame
    int new_num_elts = n + 1 - i;
    if (!ends.empty()) {
      lazy_stack_sum -= LONG(new_num_elts) * LONG(ends.back().val);
    }
    ends.push_back(StackEntry{ .idx = i, .val = n + offset });
    lazy_stack_sum += LONG(new_num_elts) * LONG(ends.back().val);
  }

  long calc_answer() {
    int ibottom = ends.empty() ? n : ends.front().idx-1;
    long sum_of_indices = prefix_sum[ibottom] + lazy_stack_sum - LONG(n)*LONG(offset);
    return LONG(n)*LONG(n+1) - sum_of_indices;
  }
};






void solve() {
  int n;
  cin >> n;
  vector<int> p(n+1);
  vector<int> p_rev(n+1);
  FORI1(n) {
    cin >> p[i];  p[i]++;
    p_rev[p[i]] = i;
  }
  PRINTVEC(p);
  Sc3developerLazyDataStructure data;
  data.n = n;
  data.original_a = vector<int>(n+1);
  int maxidx = -1;
  for (int i = 1; i <= n; i++) {
    maxidx = max(maxidx, p_rev[i]);
    data.original_a[i] = maxidx;
  }
  data.prefix_sum = vector<long>(n+1, 0);
  FORI1(n)  data.prefix_sum[i] = data.prefix_sum[i-1] + LONG(data.original_a[i]);
  data.offset = 0;
  data.ends = vector<StackEntry>();
  data.lazy_stack_sum = 0;

  long best = data.calc_answer();
  fprintf(stderr, "initial answer is %ld\n", best);
  for (int i = 1; i < n; i++) {
    int x = p[i];  //this number will be popped from front
    data.offset++;
    data.push(x);
    long ans_here = data.calc_answer();
    fprintf(stderr, "answer after popping %d is %ld\n", x, ans_here);
    best = max(best, ans_here);
  }

  cout << best << "\n";

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
