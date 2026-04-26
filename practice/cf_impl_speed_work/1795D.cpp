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













constexpr static long MOD = 998244353;
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

/* n may be reduced % MOD, but not k, O(k) */
int64_t choose_mod(int64_t n, int64_t k) {
  if (k > n)  return 0;
  int64_t top = 1; // n * ... * (n - k + 1)
  int64_t bottom = 1; // k!
  for (int64_t i = 1; i <= k; i++) {
    top = (top * ((n - i + 1) % MOD)) % MOD;
    bottom = (bottom * i) % MOD;
  }
  return (top * modular_inverse(bottom)) % MOD;
}


void solve() {
  int n;
  cin >> n;
  vector<int> weights(n);
  for (int i = 0; i < n; i++)  cin >> weights[i];
  int groups = n / 3;

  long total = 1;

  for (int group = 0; group < groups; group++) {
    int x = weights[3*group], y = weights[3*group+1], z = weights[3*group+2];
    if (y > x)  swap(x, y);
    if (z > x)  swap(x, z);
    if (z > y)  swap(y, z);

    if (x == y && y == z) {
      total *= 3;
      total %= MOD;
    } else if (y == z) {
      total *= 2;
      total %= MOD;
    } else {
      // total *= 1
    }
  }

  fprintf(stderr, "cur total %lld\n", total);

  total *= choose_mod(groups, groups/2);
  total %= MOD;
  cout << total << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
