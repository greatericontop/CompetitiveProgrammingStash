#include <bits/stdc++.h>
using namespace std;
#define long long long

//#define fprintf(...) // no-op




constexpr static long MOD = 1'000'000'007LL;

/* O(log exp) */
long mod_exp(long base, long exp) {
  long result = 1;
  while (exp > 0) {
    if (exp & 1)  result = (result * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

/* Only works for primes, O(log MOD) */
long modular_inverse(long a) {
  return mod_exp(a, MOD - 2);
}

long choose_mod(long n, long k) {
  if (k > n)  return 0;
  long top = 1; // n * ... * (n - k + 1)
  long bottom = 1; // k!
  for (long i = 1; i <= k; i++) {
    top = (top * ((n - i + 1) % MOD)) % MOD;
    bottom = (bottom * i) % MOD;
  }
  return (top * modular_inverse(bottom)) % MOD;
}





void solve() {
  assert(mod_exp(2, 29) == 536870912);
  assert((7 * modular_inverse(7)) % MOD == 1);

  long a, b, k;
  cin >> a >> b >> k;
  long R = (a-1)*k + 1;  R %= MOD;
  // choose_mod does not break if R is reduced by MOD
  long cols = choose_mod(R, a) * (b-1);  cols %= MOD;
  cols *= k;  cols++;  cols %= MOD;
  cout << R << " " << cols << "\n";
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}