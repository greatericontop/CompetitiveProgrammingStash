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




struct chash {
  // any random-ish large odd number will do
  const uint64_t C = uint64_t(2e18 * 6.76767677) + 71;
  // random 32-bit number
  const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
  size_t operator()(uint64_t x) const {
    // see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
    return __builtin_bswap64((x ^ RANDOM) * C);
  }
};
template <class K, class V> using cmap = unordered_map<K, V, chash>;









void solve() {
  int n, k;  cin >> n >> k;
  vector<int> a(n);  FORI(n)  cin >> a[i];
  int TWOK = 2*k+5;

  int best_answer = 0;  //TODO: add 1 to this at the end

  int start = 0;
  while (start < n) {
    // TODO
    cmap<int, int> counts;

    int i = 1;
    for (; start+i < n && i <= TWOK; i++) {
      int x = a[start+i] - a[start];
      if (x % i != 0)  continue;
      int d = x / i;

      // Increment counts[d], but check if it gets cut
      // In the previous index (i-1), the count must have been at least (i-1-k)
      if (counts[d] >= i-1-k) {
        counts[d]++;
      } else {
        best_answer = max(best_answer, counts[d] + k);
      }
    }

    int champion_d = -1;
    for (auto [d, count] : counts) {
      best_answer = max(best_answer, count + k);
      if (count >= TWOK-k) {
        champion_d = d;
      }
    }

    if (champion_d != -1) {
      // Keep scanning forward for the champion
      int ct = counts[champion_d];

      while (start+i < n) {
        long expected = LONG(a[start]) + LONG(champion_d)*LONG(i);
        if (a[start+i] == expected) {
          ct++;
        } else {
          // Quit if we get cut here
          if (ct < i-k) {
            assert(ct == i - k - 1);
            best_answer = max(best_answer, ct + k);
            break;
          }
        }
      }
    }

    // Increment start (maybe with cutting)
    int increment_by = max(1, i - TWOK);  //so if a loop goes long, then we don't TLE
    start += increment_by;
  }

  cout << best_answer + 1 << "\n";

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
