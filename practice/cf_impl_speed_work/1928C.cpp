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
  // 100 TC * conservative 2e5 for trial division = 2e7
  long n, x;
  cin >> n >> x;

  long ans = 0;

  set<long> answers;

  // n-x mod 2k-2 = 0
  long M = n-x;  assert(M >= 1);
  for (int h = 1; h*h<=M; h++) {
    if (M % h == 0) {
      // 2k-2 = h (h must be even)
      if (h % 2 == 0) {
        long k = (h+2)/2;
        fprintf(stderr, "h=%lld k=%lld (requires >x)\n", h, k);
        if (k >= x) {
          answers.insert(k);
          ans++;
        }
      }
      long other_h = M/h;
      if (other_h != h) {
        if (other_h % 2 == 0) {
          long k = (other_h+2)/2;
          fprintf(stderr, "h=%lld k=%lld (requires >x)\n", other_h, k);
          if (k >= x) {
            answers.insert(k);
            ans++;
          }
        }
      }
    }
  }

  // Backward pass
  M = n + x - 2;  assert(M >= 1);
  for (int h = 1; h*h<=M; h++) {
    if (M % h == 0) {
      // 2k-2 = h (h must be even)
      if (h % 2 == 0) {
        long k = (h+2)/2;
        fprintf(stderr, "h=%lld k=%lld (requires >x)\n", h, k);
        if (k >= x) {
          answers.insert(k);
          ans++;
        }
      }
      long other_h = M/h;
      if (other_h != h) {
        if (other_h % 2 == 0) {
          long k = (other_h+2)/2;
          fprintf(stderr, "h=%lld k=%lld (requires >x)\n", other_h, k);
          if (k >= x) {
            answers.insert(k);
            ans++;
          }
        }
      }
    }
  }


  cout << answers.size() << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
