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
  int n;
  cin >> n;
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];

  vector<long> prefix_sum(n+1, 0);
  for (int i = 1; i <= n; i++)  prefix_sum[i] = prefix_sum[i-1] + a[i];

  vector<int> blocks(n+1);
  blocks[1] = 0;
  for (int i = 2; i <= n; i++) {
    if (a[i] != a[i-1])  blocks[i] = blocks[i-1] + 1;
    else  blocks[i] = blocks[i-1];
  }
  PRINTVEC(blocks);

  for (int i = 1; i <= n; i++) {
    fprintf(stderr, "i=%d, a[i]=%lld\n", i, a[i]);
    int timeleft = INT_MAX, timeright = INT_MAX;
    if (i > 1) {
      int l = 0, r = i-1;
      while (l < r) {
        int j = l + (r-l+1)/2;
        long range_sum_j = prefix_sum[i-1] - prefix_sum[j-1];
        if ((blocks[j] == blocks[i-1] && a[i-1] <= a[i]) || range_sum_j <= a[i]) {
          // have to go farther left
          r = j-1;
        } else {
          l = j;
        }
      }
      if (l != 0) {
        // possible
        timeleft = i - l;
      }
    }
    if (i < n) {
      int l = i+1, r = n+1;
      while (l < r) {
        int j = l + (r-l)/2;
        long range_sum_j = prefix_sum[j] - prefix_sum[i];
        if ((blocks[j] == blocks[i+1] && a[i+1] <= a[i]) || range_sum_j <= a[i]) {
          // have to go farther right
          l = j+1;
        } else {
          r = j;
        }
      }
      fprintf(stderr, "right side index %d\n", l);
      if (l != n+1) {
        timeright = l - i;
      }
    }
    fprintf(stderr, "left %d, right %d\n", timeleft, timeright);
    int ans = min(timeleft, timeright);
    if (ans == INT_MAX)  ans = -1;
    cout << ans << " ";
  }

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
