#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif












void solve() {
  int n, m;
  cin >> n >> m;
  m--;
  vector<long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  long ops = 0;

  {
    multiset<long> vals;
    long prefix_sum = 0;
    for (int i = m + 1; i < n; i++) {
      prefix_sum += a[i];
      vals.insert(a[i]);
      if (prefix_sum < 0) {
        // flip most negative value
        auto it = vals.begin();
        prefix_sum -= 2 * (*it);
        assert(prefix_sum >= 0); // should always be doable in 1 flip
        vals.erase(it);
        ops++;
      }
    }
  }
  {
    multiset<long> vals;
    long prefix_sum = 0;
    for (int i = m; i >= 1; i--) {
      prefix_sum += a[i];
      vals.insert(a[i]);
      if (prefix_sum > 0) {
        // flip most positive value
        auto it = prev(vals.end());
        prefix_sum -= 2 * (*it);
        assert(prefix_sum <= 0);
        vals.erase(it);
        ops++;
      }
    }
  }

  cout << ops << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
