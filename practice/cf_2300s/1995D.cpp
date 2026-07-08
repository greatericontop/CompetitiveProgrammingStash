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
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










constexpr uint32_t exp(int k) {
  return ((uint32_t)1) << k;
}

void solve() {
  int n, c, k;
  cin >> n >> c >> k;
  string text;
  cin >> text;
  uint32_t expc = exp(c);

  vector<bool> allowed_masks(expc, true);

  vector<int> freq(c, 0);
  uint32_t cur_mask = 0;
  for (int i = 0; i < n; i++) {
    if (i >= k) {
      // Remove
      char ch = text[i-k];
      assert(freq[ch-'A'] > 0);
      freq[ch-'A']--;
      if (freq[ch-'A'] == 0) {
        assert(cur_mask & exp(ch-'A'));
        cur_mask ^= exp(ch-'A');
      }
    }
    // Add
    char ch2 = text[i];
    freq[ch2-'A']++;
    if (freq[ch2-'A'] == 1) {
      assert(!(cur_mask & exp(ch2-'A')));
      cur_mask |= exp(ch2-'A');
    }
    if (i >= k-1) {
      // Add to banned
      allowed_masks[cur_mask] = false;
    }
  }
  // Also ban the last character
  char last = text[n-1];
  allowed_masks[exp(last-'A')] = false;


  int best_exclusion = -1;

  vector<vector<uint32_t>> masks_by_size(c+1);
  for (uint32_t mask = 0; mask < expc; mask++) {
    masks_by_size[__builtin_popcount(mask)].pb(mask);
  }

  for (int size = 0; size <= c; size++) {
    for (uint32_t mask : masks_by_size[size]) {
      if (!allowed_masks[mask]) {
        // Disallowed, propagate it
        for (int extra = 0; extra < c; extra++) {
          uint32_t also_ban = mask | exp(extra);
          allowed_masks[also_ban] = false;
        }
      } else {
        // Allowed
        best_exclusion = max(best_exclusion, size);
      }
    }
  }

  assert(best_exclusion != -1);

  cout << c-best_exclusion << "\n";

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
