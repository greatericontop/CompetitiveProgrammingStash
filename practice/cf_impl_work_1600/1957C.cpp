#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d %d, ", _x.first, _x.second); \
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










constexpr long MOD = 1'000'000'007LL;
long FACTORIALS[300010];
/* O(log exp) */
int64_t mod_exp(int64_t base, int64_t exp) {
  int64_t result = 1;
  while (exp > 0) {
    if (exp & 1)  result = (result * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

/* Only works for primes, O(log MOD) */
int64_t modular_inverse(int64_t a) {
  return mod_exp(a, MOD - 2);
}


void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    int ri, ci;
    cin >> ri >> ci;
    if (ri == ci) {
      n--;
    } else {
      n -= 2;
    }
  }
  fprintf(stderr, "board reduces to n = %d\n", n);

  long ans = 0;
  for (int x = 0; x <= n; x += 2) {
    // (n choose n-x) places to place diagonals
    // reduce to board of size x (x is even), where we have x! arrangements
    // = n! / (n-x)!
    // Divide by x/2 ! for ordering
    long ways = (FACTORIALS[n] * modular_inverse(  (FACTORIALS[n-x] * FACTORIALS[x/2]) % MOD  )) % MOD;
    ans += ways;
    ans %= MOD;
    fprintf(stderr, "+%d for x=%d\n", ways, x);
  }

  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  FACTORIALS[0] = 1;
  for (int i = 1; i <= 300000; i++) {
    FACTORIALS[i] = FACTORIALS[i-1] * i;
    FACTORIALS[i] %= MOD;
  }
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
