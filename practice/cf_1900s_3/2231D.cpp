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






long BIGNEG = LONG(-1e14);

/* Try to satisfy poi, in range between POIs x and y. Actually sets values a[x+1...y]. */
bool solve_poi(int x, int y, vector<long>& a, const vector<bool>& locked, const vector<long>& c) {
  long required_sum = c[y] - c[x];
  long current_sum = 0;
  int num_blanks = 0, left_blank = INT_MAX, right_blank = INT_MIN;
  for (int i = x+1; i <= y; i++) {
    if (locked[i]) {
      current_sum += a[i];
    } else {
      assert(a[i] == 0);
      num_blanks++;
      left_blank = min(left_blank, i);
      right_blank = max(right_blank, i);
    }
  }
  if (num_blanks == 1) {
    // 1 blank: forced what number to put
    a[left_blank] = required_sum - current_sum;
  } else if (num_blanks >= 2) {
    // >= 2 blanks: put huge negative in leftmost and revert in rightmost
    a[left_blank] = BIGNEG;  current_sum += a[left_blank];
    a[right_blank] = required_sum - current_sum;
  }

  // final check
  long sum = 0;
  for (int i = x+1; i <= y; i++) {
    sum += a[i];
    if (i < y && sum > 0) {  //c[i] = c[x] + sum  --->  sum cannot exceed 0 or else violate prefix max condition
      return false;
    }
  }
  if (sum == required_sum)  return true;
  return false;
}
bool solve_last(int x, int n, vector<long>& a, const vector<bool>& locked, const vector<long>& c) {
  long sum = 0;
  for (int i = x+1; i <= n; i++) {
    if (locked[i]) {
      sum += a[i];
      if (sum > 0)  return false;  //c[i] just can't exceed the final prefix max
    } else {
      a[i] = BIGNEG;
      return true;
    }
  }
  return true;
}





void solve() {
  int n;
  cin >> n;
  string s;  cin >> s;
  vector<bool> locked(n+1);
  for (int i = 1; i <= n; i++)  locked[i] = (s[i-1] == '1');
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];
  vector<long> c(n+1, 0);
  FORI1(n)  cin >> c[i];

  vector<int> poi;
  poi.pb(1);
  for (int i = 2; i <= n; i++) {
    if (c[i-1] > c[i]) {
      cout << "NO\n";
      return;
    }
    if (c[i] != c[i-1])  poi.pb(i);
  }
  PRINTVEC(poi);

  if (locked[1]) {
    if (a[1] != c[1]) {
      cout << "NO\n";
      return;
    }
  } else {
    a[1] = c[1];
  }

  for (int i = 0; i < INT(poi.size())-1; i++) {
    if (!solve_poi(poi[i], poi[i+1], a, locked, c)) {
      fprintf(stderr, "fail %d to %d\n", poi[i], poi[i+1]);
      cout << "NO\n";
      return;
    }
  }
  if (!solve_last(poi.back(), n, a, locked, c)) {
    fprintf(stderr, "fail last\n");
    cout << "NO\n";
    return;
  }

  cout << "YES\n";
  for (int i = 1; i <= n; i++)  cout << a[i] << " ";
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
