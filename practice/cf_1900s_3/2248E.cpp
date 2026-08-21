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







constexpr long MAX = LONG(3e18);
struct Fraction {
  long num;
  long den;

  bool operator < (const Fraction& other) const {
    assert(num >= 0 && den > 0 && num <= MAX && den <= MAX);
    assert(other.num >= 0 && other.den > 0 && other.num <= MAX && other.den <= MAX);
    __int128 lhs = ((__int128) num) * ((__int128) other.den);
    __int128 rhs = ((__int128) other.num) * ((__int128) den);
    return lhs < rhs;
  }
};



void solve() {
  long n;  int m;  long d;
  cin >> n >> m >> d;
  vector<long> p(m), r(m);
  FORI(m)  cin >> p[i] >> r[i];

  long sigmari = accumulate(r.begin(), r.end(), 0LL);
  Fraction default_rate = {n*d + sigmari, n};  //10^9*10^9 + 10^15
  fprintf(stderr, "default_rate = %ld/%ld\n", default_rate.num, default_rate.den);
  Fraction best_alt_rate = default_rate;

  long sigmari_so_far = 0;
  for (int i = 0; i < m; i++) {
    sigmari_so_far += r[i];
    long xmin = p[i];
    long xmax = i == m-1 ? n-1 : p[i+1] - 1;  //since doing n is pointless

    // rate = d + (sigma ri - d) / (x+1)
    //   obvious choice is xmin or xmax
    // rate = (x*d + sigma ri) / (x+1)
    Fraction rate1 = {xmin*d + sigmari_so_far, xmin+1};
    Fraction rate2 = {xmax*d + sigmari_so_far, xmax+1};
    fprintf(stderr, "rate1 (x=%ld): %ld/%ld\n", xmin, rate1.num, rate1.den);
    fprintf(stderr, "rate2 (x=%ld): %ld/%ld\n", xmax, rate2.num, rate2.den);
    best_alt_rate = max(best_alt_rate, max(rate1, rate2));
  }
  fprintf(stderr, "best_alt_rate = %ld/%ld\n", best_alt_rate.num, best_alt_rate.den);

  if (default_rate < best_alt_rate) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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
