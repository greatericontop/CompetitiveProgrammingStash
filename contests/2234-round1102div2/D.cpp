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
  string x, y;
  cin >> x >> y;
  string x_xor_y(n, '.');
  FORI(n)  x_xor_y[i] = (x[i] == y[i]) ? '0' : '1';
  long x0 = 0, x1 = 0, y0 = 0, y1 = 0, xor0 = 0, xor1 = 0;
  FORI(n) {
    if (x[i] == '0')  x0++;
    else  x1++;
    if (y[i] == '0')  y0++;
    else  y1++;
    if (x_xor_y[i] == '0')  xor0++;
    else  xor1++;
  }
  long score_x = x0*x1, score_y = y0*y1, score_xor = xor0*xor1;


  /*
   * Kentq rec spec:
   *
   *   dp_xy[k] = score of 0...2^k (INCLUSIVE) if 0 is x and 2^k is y
   *
   *   dp[0] would be 2 elts
   */
  vector<long> dp_xy(k+1, -1);
  // x y
  dp_xy[0] = score_x + score_y;
  dp_xy[1] = score_x + score_y + score_xor;
  for (int i = 2; i <= k; i++) {
    // i turns into 2x i-2 and 1x i-1, minus y and x on the boundaries
    dp_xy[i] = 2*dp_xy[i-2] + dp_xy[i-1] - score_x - score_y;
  }

  cout << dp_xy[k] << "\n";


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
