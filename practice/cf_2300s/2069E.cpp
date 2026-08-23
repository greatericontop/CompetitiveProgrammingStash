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










void solve() {
  string s;  cin >> s;  int n = s.size();
  int a, b, ab, ba;  cin >> a >> b >> ab >> ba;

  int open_pairs = 0;
  vector<int> ab_sizes, ba_sizes;
  int start = 0;
  for (int i = 1; i <= n; i++) {
    if (i == n || s[i] == s[i-1]) {
      string t = s.substr(start, i - start);

      if (t.front() == t.back()) {
        // unbalanced
        assert(t.size() % 2 == 1);
        open_pairs += t.size() / 2;  //rounded down
        if (t.front() == 'A')  a--;
        else  b--;
      } else {
        assert(t.size() % 2 == 0);
        if (t.front() == 'A')  ab_sizes.push_back(t.size() / 2);  //ABABAB
        else  ba_sizes.push_back(t.size() / 2);
      }

      start = i;
    }
  }
  sort(ab_sizes.begin(), ab_sizes.end());
  sort(ba_sizes.begin(), ba_sizes.end());
  int cur_ab = accumulate(ab_sizes.begin(), ab_sizes.end(), 0);
  int cur_ba = accumulate(ba_sizes.begin(), ba_sizes.end(), 0);
  fprintf(stderr, "ab %d/%d, ba %d/%d, open pairs %d\n", cur_ab, ab, cur_ba, ba, open_pairs);
  fprintf(stderr, "a %d, b %d (after adjustment)\n", a, b);

  auto distribute = [&](int am) {
    if (cur_ab < ab) {
      int need = ab - cur_ab;
      int take = min(need, am);
      cur_ab += take;
      am -= take;
    }
    cur_ba += am;
  };
  // Add opens to AB until capacity, then rest to BA
  distribute(open_pairs);

  int num_singles = min(a, b);
  if (num_singles < 0) {
    cout << "NO\n";
    return;
  }

  // One of them is over and other is not
  if ((cur_ab > ab) ^ (cur_ba > ba)) {
    if (cur_ab > ab) {
      // Donating cur_ab to cur_ba
      while (cur_ab > ab && cur_ba < ba && !ab_sizes.empty()) {
        int sz = ab_sizes.back();  ab_sizes.pop_back();  //largest first
        cur_ab -= sz;
        num_singles--;  sz--;  //turn one ab into singles, this also frees up the rest of sz
        distribute(sz);
      }
    } else {
      // Donating cur_ba to cur_ab
      while (cur_ba > ba && cur_ab < ab && !ba_sizes.empty()) {
        int sz = ba_sizes.back();  ba_sizes.pop_back();
        cur_ba -= sz;
        num_singles--;  sz--;
        distribute(sz);
      }
    }
  }

  // Now, both are under or both are over (or equal)
  // So just convert to singles now
  if (cur_ab > ab) {
    int lose = cur_ab - ab;
    num_singles -= lose;
  }
  if (cur_ba > ba) {
    int lose = cur_ba - ba;
    num_singles -= lose;
  }

  if (num_singles < 0) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
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
