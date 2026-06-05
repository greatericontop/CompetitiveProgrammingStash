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
constexpr static long MOD =   998'244'353LL;










/* sqrt x, returns prime factors as a set (not multiset) */
vector<long> brute_factor(long x) {
  set<long> ret;
  for (long i = 2; i*i <= x; i++) {
    if (x % i == 0) {
      ret.insert(i);
      do {
        x /= i;
      } while (x % i == 0);
    }
  }
  if (x > 1)  ret.insert(x);
  return vector<long>(ret.begin(), ret.end());
}


void solve() {
  int n; long m;
  cin >> n >> m;
  vector<long> a(n);
  FORI(n)  cin >> a[i];

  // Max TC per test: n + 30,000 + 30*512

  long total = 1;
  for (int i = 0; i < n-1; i++) {
    // a[i], a[i+1]  (to set b[i+1]) (b[0] is fixed)
    if (a[i] % a[i+1] != 0) {
      cout << 0 << "\n";
      return;
    }
    long v = a[i] / a[i+1];
    long lim = m / a[i+1];
    // Factor v, then count how many x in [1...lim] share a factor with v (rest are relatively prime)
    vector<long> factors = brute_factor(v);
    int k = factors.size();
    long ct = 0;
    for (int subset = 1; subset < (1 << k); subset++) {
      long product = 1;
      for (int j = 0; j < k; j++) {
        if (subset & (1 << j))  product *= factors[j];
      }
      if (__builtin_popcount(subset) % 2 == 1) {
        ct += lim / product;
      } else {
        ct -= lim / product;
      }
    }
    ct = lim - ct;
    total = (total * ct) % MOD;
  }

  cout << total << "\n";

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
