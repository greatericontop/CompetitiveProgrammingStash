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
  vector<int> c(n);
  FORI(n)  cin >> c[i];
  int k;
  cin >> k;
  vector<int> suffix_min(n+1, INT_MAX);
  for (int i = n-1; i >= 0; i--)  suffix_min[i] = min(suffix_min[i+1], c[i]);

  vector<int> usages(n);
  int usages_required = k / suffix_min[0];
  for (int i = 0; i < n; i++) {
    // Place minimum possible at i, leaving as much as possible for i+1, while having usages_required met
    if (c[i] >= suffix_min[i+1]) {
      // Makes no sense to use us, no-op
      fprintf(stderr, "skip i=%d\n", i);
    } else {
      // bin search on minimal number of times we can use c[i]
      int l = 0, r = usages_required;
      while (l < r) {
        int usages_ci = l + (r-l)/2;
        int usages_left = usages_required - usages_ci;
        int k_left = k - usages_ci*c[i];
        int max_usages_next = k_left / suffix_min[i+1];
        if (max_usages_next >= usages_left) {
          r = usages_ci;
        } else {
          l = usages_ci + 1;
        }
      }
      if (i == n-1)  assert(l == usages_required);
      fprintf(stderr, "i=%d, k=%d, use usages[i]=%d of required here %d\n", i, k, l, usages_required);
      usages[i] = l;
      usages_required -= l;
      k -= l*c[i];
      assert(k >= 0);
    }
  }

  vector<int> a(n+1, 0);  //suffix sum of usages
  for (int i = n-1; i >= 0; i--)  a[i] = a[i+1] + usages[i];

  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
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
