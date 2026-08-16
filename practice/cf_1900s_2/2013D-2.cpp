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
    if (stack[0].x < stack[1].x) {
      return;
    }
    long sum = stack[0].x * stack[0].ct + stack[1].x * stack[1].ct;
    int total_ct = stack[0].ct + stack[1].ct;
    long avg = sum / total_ct;
    int rem = sum % total_ct;
    if (rem == 0) {
      stack.clear();
      stack.pb(Entry{avg, total_ct});
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

    long sum = second.x * second.ct + top_x;
    int total_ct = second.ct + 1;
    long avg = sum / total_ct;
    if (avg >= third.x) {
      // plain merge works
      stack.pop_back();
      stack.pop_back();
      int rem = sum % total_ct;
      Entry e1 = Entry{avg, total_ct - rem};
      if (e1.x == stack.back().x) {
        stack.back().ct += e1.ct;
      } else {
        stack.pb(e1);
      }
      Entry e2 = Entry{avg+1, rem};
      if (e2.ct > 0) {
        stack.pb(e2);
      }
      fprintf(stderr, "  perfromed plain merge\n");
    } else {
      // merge second into third and recurse
      stack.pop_back();
      stack.pop_back();
      stack.back().ct += second.ct;
      long new_top_x = top_x + (second.x - third.x)*second.ct;
      assert(new_top_x < third.x);
      stack.pb(Entry{new_top_x, 1});
      fprintf(stderr, "  merging recursively\n");
      fix_top_2_atleast3();
    }
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
