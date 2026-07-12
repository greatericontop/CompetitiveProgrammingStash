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
constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;





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
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  int istart = 0;
  while (istart < n && a[istart] == -1)  istart++;  //istart is the number of -1s, and the index of the first real elt

  long waiting_no1 = 1;  //empty sequence
  long waiting_yes1 = 0;
  map<int, long> one_no1;
  map<int, long> one_yes1;

  for (int i = istart; i < n; i++) {
    long delta_waiting_no1 = 0, delta_waiting_yes1 = 0;
    // one_yes1 ---> waiting_yes1,  by taking the same value
    delta_waiting_yes1 += one_yes1[a[i]];
    // one_no1 ---> waiting_no1,  by taking the same value
    delta_waiting_no1 += one_no1[a[i]];
    // one_no1 ---> waiting_yes1,  by taking value+1 (which is -1 from cur)
    delta_waiting_yes1 += one_no1[a[i] - 1];

    // waiting_no1 ---> one_no1
    one_no1[a[i]] += waiting_no1;
    one_no1[a[i]] %= MOD;
    // waiting_yes1 ---> one_yes1
    one_yes1[a[i]] += waiting_yes1;
    one_yes1[a[i]] %= MOD;

    waiting_no1 += delta_waiting_no1;
    waiting_yes1 += delta_waiting_yes1;
    waiting_no1 %= MOD;  waiting_yes1 %= MOD;
  }

  long ans1 = waiting_yes1;
  fprintf(stderr, "first ans: %lld\n", ans1);
  // number of ways to pick odd 1s = (istart choose 1) + (istart choose 3) + ...
  long multi = istart == 0 ? 0 : mod_exp(2, istart - 1);
  ans1 *= multi;
  ans1 %= MOD;




  // accumulating pairs
  long ans2 = 1;
  map<int, long> inprogress;
  for (int i = 0; i < n; i++) {
    long ans2_delta = inprogress[a[i]];
    inprogress[a[i]] += ans2;
    inprogress[a[i]] %= MOD;
    ans2 += ans2_delta;
    ans2 %= MOD;
  }
  fprintf(stderr, "second ans: %lld\n", ans2);

  cout << (ans1 + ans2) % MOD << "\n";


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
