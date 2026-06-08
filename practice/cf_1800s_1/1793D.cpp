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










constexpr static long SUBARRS(long sz) {
  return sz * (sz + 1) / 2;
}

void solve() {
  int n;
  cin >> n;
  vector<int> p(n+1);
  vector<int> q(n+1);
  FORI1(n)  cin >> p[i];
  FORI1(n)  cin >> q[i];
  vector<int> p_inv(n+1);
  FORI1(n)  p_inv[p[i]] = i;
  vector<int> q_inv(n+1);
  FORI1(n)  q_inv[q[i]] = i;

  long ans = 0;
  // no 1
  int i = p_inv[1];
  int j = q_inv[1];
  if (i > j)  swap(i, j);
  ans += SUBARRS(i-1);
  ans += SUBARRS(j-i-1);
  ans += SUBARRS(n-j);

  int left = i, right = j;
  for (int x = 1; x <= n; x++) {
    // include x, but not x+1
    int exclude1 = p_inv[x+1];
    int exclude2 = q_inv[x+1];
    if (left <= exclude1 && exclude1 <= right) {
      // zero here, just update
    } else if (left <= exclude2 && exclude2 <= right) {
      // zero here, just update
    } else {
      int left_bound = 1;
      if (exclude1 < left)  left_bound = max(left_bound, exclude1+1);
      if (exclude2 < left)  left_bound = max(left_bound, exclude2+1);
      int right_bound = n;
      if (exclude1 > right)  right_bound = min(right_bound, exclude1-1);
      if (exclude2 > right)  right_bound = min(right_bound, exclude2-1);
      long left_ways = max(0, left - left_bound + 1);
      long right_ways = max(0, right_bound - right + 1);
      ans += left_ways * right_ways;
    }

    left = min(left, min(exclude1, exclude2));
    right = max(right, max(exclude1, exclude2));
  }

  cout << ans << "\n";

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
