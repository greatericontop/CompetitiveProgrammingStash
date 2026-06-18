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
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
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










void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;


  vector<int> chain_lengths(n);
  vector<int> suffix_lengths(n);
  chain_lengths[n-1] = 1;
  suffix_lengths[n-1] = 1;
  bool in_first = true;
  for (int i = n-2; i >= 0; i--) {
    if (s[i] == s[i+1]) {
      if (in_first) {
        suffix_lengths[i] = suffix_lengths[i+1] + 1;
        if (suffix_lengths[i] > k)  suffix_lengths[i] = INT_MIN;  // invalid
      }
      chain_lengths[i] = chain_lengths[i+1] + 1;
      if (chain_lengths[i] > k)  chain_lengths[i] = INT_MIN;  // invalid
    } else {
      chain_lengths[i] = (in_first || chain_lengths[i+1] == k) ? 1 : INT_MIN;
      if (in_first) {
        in_first = false;
        for (int j = 0; j <= i; j++)  suffix_lengths[j] = suffix_lengths[i+1];
      }
    }
  }

  fprintf(stderr, "%s\n", s.c_str());
  PRINTVEC(chain_lengths);
  PRINTVEC(suffix_lengths);

  // sweeping possible locations of p
  char cur_char = s[0];
  int cur_count = 1;
  for (int p = 0; p < n; p++) {
    if (p != 0) {
      if (s[p] == cur_char) {
        cur_count++;
        if (cur_count > k)  break;  //no longer valid
      } else {
        if (cur_count != k)  break;
        cur_char = s[p];
        cur_count = 1;
      }
    }
    // Otherwise we're valid, check if we can make the rest
    if (p != n-1) {
      // check if cur_char matches s[n-1]
      if (cur_char == s[n-1]) {
        // chain there must be valid
        if (chain_lengths[p+1] == k && suffix_lengths[p+1] + cur_count == k) {
          cout << p+1 << "\n";
          return;
        }
      } else {
        // if different, both must k
        if (chain_lengths[p+1] == k && suffix_lengths[p+1] == k) {
          cout << p+1 << "\n";
          return;
        }
      }
    } else {
      // special case if we're at the end
      if (cur_count == k) {
        cout << p+1 << "\n";
        return;
      }
    }
  }

  cout << -1 << "\n";

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
