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
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }










constexpr static inline bool isset(long x, int bit) {
  return (x >> bit) & 1;
}

constexpr static long INF = LONG(2e18);

void solve() {
  int n, q;
  cin >> n >> q;
  vector<long> a_orig(n);
  FORI(n)  cin >> a_orig[i];

  while (q--) {
    vector<long> a = a_orig;
    long k;
    cin >> k;

    long mask = 0;
    for (int bit = 59; bit >= 0; bit--) {
      fprintf(stderr, "bit %d\n", bit);
      long cost_of_this_bit = 0;
      vector<long> diffs(n);
      for (int i = 0; i < n; i++) {
        if (isset(a[i], bit)) {
          fprintf(stderr, "  a[%d] is set\n", i);
          diffs[i] = 0;
        } else {
          long exp = 1LL << bit;
          long target = (a[i]/exp + 1) * exp;
          fprintf(stderr, "  a[%d] is not set, target is %lld\n", i, target);
          assert(target - a[i] > 0);
          assert(isset(target, bit));
          diffs[i] = target - a[i];
          cost_of_this_bit += diffs[i];
          if (cost_of_this_bit > INF)  cost_of_this_bit = INF;
        }
      }
      if (cost_of_this_bit <= k) {
        k -= cost_of_this_bit;
        for (int i = 0; i < n; i++) {
          a[i] += diffs[i];
        }
        mask |= (1LL << bit);
        fprintf(stderr, "  applying this bit, for a cost of %lld\n", cost_of_this_bit);
        PRINTVECL(a);
      }  //otherwise ignore
    }
    fprintf(stderr, "final mask: %lld\n", mask);
    long acc = accumulate(a.begin(), a.end(), (1LL<<62)-1, [](long sum, long x) { return sum & x; });
    fprintf(stderr, "final accumulated: %lld\n", acc);
    assert(mask == acc);
    cout << mask << "\n";
  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
