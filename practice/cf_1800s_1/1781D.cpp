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









constexpr static long MAXIM = LONG(1e9) * LONG(1e9);

void solve() {
  int n;
  cin >> n;
  vector<long> a(n);
  FORI(n)  cin >> a[i];

  int best = 1;
  for (int i = 0; i < n-1; i++) {
    for (int j = i+1; j < n; j++) {
      // a[i], a[j] are guaranteed within the set
      long difference = a[j] - a[i];
      for (long divisions = 1; divisions*divisions <= difference; divisions++) {
        if (difference % divisions != 0)  continue;
        long avg = difference / divisions;
        if (divisions % 2 == 0 && avg % 2 == 1)  continue;
        if (divisions % 2 == 1 && avg % 2 == 0)  continue;
        long low_diff = avg - divisions + 1;
        long high_diff = avg + divisions - 1;
        long _l = (low_diff-1)/2;  long low_sq = _l*_l;
        long _r = (high_diff+1)/2;  long high_sq = _r*_r;
        if (_l < 0)  continue;
        fprintf(stderr, "%lld and %lld  :  diff %lld avg %lld _l %lld _r %lld\n", a[i], a[j], difference, avg, _l, _r);
        assert(high_sq - low_sq == difference);
        long x = low_sq - a[i];
        if (x >= 0 && x <= MAXIM) {
          int ans = 0;
          for (int k = 0; k < n; k++) {
            long val = a[k] + x;
            long s = (long) sqrt(val);
            if (s*s == val)  ans++;
          }
          fprintf(stderr, "  x %lld  ans %d\n", x, ans);
          best = max(best, ans);
        }
      }
    }
  }

  cout << best << "\n";

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
