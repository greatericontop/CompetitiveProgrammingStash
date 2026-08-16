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
  long x;
  int ct;
};

struct State {
  vector<Entry> stack;

  void fix_top_2_only2() {
    fprintf(stderr, "fix top 2 called on:  ");  print();
    if (stack.size() == 1) {
      return;
    }
    assert(stack.size() == 2);
    long sum = stack[0].x * stack[0].ct + stack[1].x * stack[1].ct;
    int total_ct = stack[0].ct + stack[1].ct;
    long avg = sum / total_ct;
    int rem = sum % total_ct;
    if (rem == 0) {
      stack.clear();
      stack[0] = Entry{avg, total_ct};
    } else {
      stack[0] = Entry{avg, total_ct - rem};
      stack[1] = Entry{avg+1, rem};
    }
    print();
  }

  void fix_top_2_atleast3() {
    if (stack.size() < 3) {
      fix_top_2_only2();
      return;
    }
    assert(stack.back().ct == 1);
    long top_x = stack.back().x;
    Entry second = stack[stack.size()-2];
    Entry third = stack[stack.size()-3];

    if (top_x > second.x) {
      // already good
      return;
    } else if (top_x == second.x) {
      // merge top into second
      stack.pop_back();
      stack[stack.size()-1].ct += 1;
      return;
    }

    long max_decrement_in_middle = second.x - third.x;
    long top_x_missing = second.x - top_x;

    long elts_requested = top_x_missing / max_decrement_in_middle;
    long extra_requested = top_x_missing % max_decrement_in_middle;
    long elts_required = elts_requested + (extra_requested > 0 ? 1 : 0);
    fprintf(stderr, "missing: %ld;  elts requested %ld, extra requested %ld\n", top_x_missing, elts_requested, extra_requested);
    if (elts_required > second.ct) {
      // second will merge into third, and then recurse
      stack.pop_back();
      stack.pop_back();
      stack[stack.size()-1].ct += second.ct;
      // top is partially incremented
      stack.pb(Entry{top_x + second.ct*max_decrement_in_middle, 1});
      fprintf(stderr, "  recurse on:  ");  print();
      fix_top_2_atleast3();
      return;
    }
    // otherwise
    Entry new_third = third;
    Entry new_second = second;
    new_third.ct += elts_requested;
    new_second.ct -= elts_requested;
    new_second.ct += 1;  //for top
    Entry between = Entry{second.x - extra_requested, 1};
    stack.pop_back();
    stack.pop_back();
    stack.pop_back();
    stack.pb(new_third);
    stack.pb(between);
    stack.pb(new_second);
  }

  void print() {
    for (const auto& e : stack) {
      fprintf(stderr, "[");
      if (e.ct <= 0)  fprintf(stderr, "%ld x%d", e.x, e.ct);
      for (int i = 0; i < e.ct; i++) {
        fprintf(stderr, "%ld%s", e.x, (i == e.ct-1 ? "" : " "));
      }
      fprintf(stderr, "] ");
    }
    fprintf(stderr, "\n");
  }

};





void solve() {
  int n;
  cin >> n;
  vector<long> a(n);
  FORI(n)  cin >> a[i];
  State state;  state.stack = vector<Entry>();
  for (int i = 0; i < n; i++) {
    state.stack.pb(Entry{a[i], 1});
    fprintf(stderr, "before fix:  "); state.print();
    state.fix_top_2_atleast3();
    fprintf(stderr, "after fix:   "); state.print();
  }
  long ans = state.stack.back().x - state.stack.front().x;
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
