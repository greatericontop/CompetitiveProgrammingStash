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










void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  string s;
  cin >> s;
  s = '.' + s;
  set<int> active_set;
  for (int x = 1; x <= n; x++)  active_set.insert(x);
  vector<int> ordering;
  FORI(m) {
    int l, r;
    cin >> l >> r;
    while (true) {
      auto it = active_set.lower_bound(l);
      if (it == active_set.end() || *it > r)  break;
      ordering.pb(*it);
      active_set.erase(it);
    }
  }
  PRINTVEC(ordering);

  int ones_in_string = 0;
  for (char c : s)  if (c == '1')  ones_in_string++;
  int ones_requested = min(ones_in_string, INT(ordering.size()));
  vector<bool> requested(n+1);
  for (int i = 0; i < ones_requested; i++)  requested[ordering[i]] = true;
  vector<bool> ones(n+1);
  for (int i = 1; i <= n; i++)  ones[i] = (s[i] == '1');
  int crossproduct = 0;
  for (int i = 1; i <= n; i++)  if (requested[i] && ones[i])  crossproduct++;

  while (q --> 0) {
    int idx;
    cin >> idx;

    crossproduct -= (requested[idx] && ones[idx]);
    if (ones[idx]) {
      ones[idx] = false;
      ones_in_string--;
      ones_requested = min(ones_in_string, INT(ordering.size()));
      if (ones_in_string < INT(ordering.size())) {
        if (ordering[ones_in_string] != idx)  crossproduct -= (requested[ordering[ones_in_string]] && ones[ordering[ones_in_string]]);
        requested[ordering[ones_in_string]] = false;
      }
    } else {
      ones[idx] = true;
      ones_in_string++;
      ones_requested = min(ones_in_string, INT(ordering.size()));
      if (ones_in_string <= INT(ordering.size())) {
        requested[ordering[ones_in_string-1]] = true;
        if (ordering[ones_in_string-1] != idx)  crossproduct += (requested[ordering[ones_in_string-1]] && ones[ordering[ones_in_string-1]]);
      }
    }
    crossproduct += (requested[idx] && ones[idx]);

    // number of operations required is (ones requested) - (crossproduct)
    cout << (ones_requested - crossproduct) << "\n";
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
