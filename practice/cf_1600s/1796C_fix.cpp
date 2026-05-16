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
  // size, with bonus
  if (r >= 3*l) {
    long maxstart = r / (3 * exp(size - 2));
    assert(maxstart * 3 * exp(size - 2) <= r);
    assert((maxstart + 1) * 3 * exp(size - 2) > r);
    if (maxstart >= l) {
      ans += (maxstart - l + 1) * (size - 1); // will be doublecounted later
      ans %= MOD;
    }
  }
  fprintf(stderr, "maxstart = %lld, giving us %lld\n", maxstart, ans);
  // size, without bonus
  long maxstart = r / exp(size-1);
  assert(maxstart * exp(size-1) <= r);
  assert((maxstart+1) * exp(size-1) > r);
  assert(maxstart >= l);
  ans += (maxstart - l + 1);
  ans %= MOD;

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
