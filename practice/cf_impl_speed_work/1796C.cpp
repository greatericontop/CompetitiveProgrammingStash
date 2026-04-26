#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


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















#define exp(x) (1LL << (x))
constexpr static long MOD = 998244353;

void solve() {
  long l, r;
  cin >> l >> r;

  // find size
  int size = 1;
  long x = l;
  while (2*x <= r) {
    size++;
    x *= 2;
  }
  assert(l * exp(size-1) <= r);
  assert(l * exp(size) > r);
  assert(size <= 30);

  long ans = 0;
  for (long start = l; start <= r; start++) {
    if (start * exp(size-1) > r)  break;

    if (start * exp(size-2) * 3 <= r) {
      // if size=4
      //  start, 2, 2, 2
      //  start, 2, 2, 3
      //         3  3
      ans += size;
      ans %= MOD;
    } else {
      ans += 1;
      ans %= MOD;
    }
  }

  cout << size << " " << ans << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  if (!(cin >> t)) {
    cerr << "I love larping as a cheater\n";
  }
  while (t--)  solve();
  return 0;
}
