#include <bits/stdc++.h>
using namespace std;


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
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
using pairii = pair<int, int>;
using pairll = pair<long, long>;










void solve() {
  int n;
  cin >> n;
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  long l = 0, h = 5e17;
  vector<long> b(n);
  while (l < h) {  // n*64
    long increments = l + (h-l)/2;
    bool breaknow = false;
    for (int i = 0; i < n; i++) {
      b[i] = a[i] + increments;
      if (b[i] < 0) {
        breaknow = true;
      }
    }
    if (breaknow) {
      l = increments+1;
      continue;
    }
    long cur = b[0];
    long required_size = 0;
    bool success = true;
    for (int i = 1; i < n; i++) {
      // up to :cur: decrements, to decrease b to required_size
      if (b[i] < required_size) {
        success = false;
        break;
      }
      long num_decrements = min(cur, b[i]-required_size);
      cur = num_decrements;
      required_size = b[i]-num_decrements;
    }
    if (success) {
      h = increments;
    } else {
      l = increments+1;
    }
  }

  fprintf(stderr, "number of increments: %lld\n", l);
  long increments = l;
  for (int i = 0; i < n; i++) {
      b[i] = a[i] + increments;
  }
  long cur = b[0];
  long required_size = 0;
  for (int i = 1; i < n; i++) {
    // up to :cur: decrements, to decrease b to required_size
    if (b[i] < required_size) {
      break;
    }
    long num_decrements = min(cur, b[i]-required_size);
    cur = num_decrements;
    required_size = b[i]-num_decrements;
  }
  long ans = increments + b[0] + required_size;
  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
