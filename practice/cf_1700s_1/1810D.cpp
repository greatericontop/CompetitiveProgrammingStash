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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










struct Interval {
  long low;
  long high;
};

void solve() {
  int q;
  cin >> q;
  Interval interval = {1, LONG(2e18)};
  while (q--) {
    assert(interval.low <= interval.high);

    int type; cin >> type;

    if (type == 1) {
      // Update interval

      long a, b, n; cin >> a >> b >> n;
      long low_h;
      if (n > 1) {
        low_h = (a-b)*(n-1) + b + 1;
      } else {
        low_h = 1;
      }
      long high_h = (a-b)*(n-1) + a;
      assert(low_h <= high_h);

      fprintf(stderr, "Query: a=%lld b=%lld n=%lld   low_h=%lld high_h=%lld\n", a, b, n, low_h, high_h);
      if (low_h > interval.high || high_h < interval.low) {
        cout << "0 ";
      } else {
        interval.low = max(interval.low, low_h);
        interval.high = min(interval.high, high_h);
        cout << "1 ";
      }

    } else {
      // Query

      long a, b; cin >> a >> b;
      long ans1 = interval.low <= a ? 1 : ceildivl(interval.low-a, a-b) + 1;
      long ans2 = interval.high <= a ? 1 : ceildivl(interval.high-a, a-b) + 1;
      fprintf(stderr, "Query: a=%lld b=%lld   low=%lld high=%lld   ans1=%lld ans2=%lld\n", a, b, interval.low, interval.high, ans1, ans2);
      if (ans1 == ans2) {
        cout << ans1 << " ";
      } else {
        cout << -1 << " ";
      }

    }

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
