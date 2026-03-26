#include <bits/stdc++.h>
using namespace std;





constexpr static long MOD = 1'000'000'007LL;

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





int main() {
  assert(mod_exp(2, 29) == 536870912LL);
  assert(mod_exp(67, 67) == 680469276LL);
  assert(mod_exp(123456789, 123456789) == 907408795LL);
  assert((7 * modular_inverse(7)) % MOD == 1);
  assert((185372 * modular_inverse(185372)) % MOD == 1);
  assert(modular_inverse(59283) == 628072133LL);
  assert(choose_mod(5, 2) == 10);
  assert(choose_mod(676767, 150) == (choose_mod(676766, 150) + choose_mod(676766, 149)) % MOD);
  assert(choose_mod(57, 13) == 296022564LL);
  assert(choose_mod(1875, 22) == 252566709LL);
  assert(choose_mod(458723, 37102) == 577730621LL);
  // std::gcd
  assert(gcd(12, 15) == 3);
  assert(gcd(132548923592LL, 128472357632LL) == 8);
  assert(gcd(3282296664LL, 14107131210LL) == 11240742LL);
  cout << "All tests passed!\n";

  return 0;
}
