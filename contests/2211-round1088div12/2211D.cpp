#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op




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

long FACTORIALS[300001];
void init_factorials() {
  FACTORIALS[0] = 1;
  for (int i = 1; i <= 300000; i++) {
    FACTORIALS[i] = (FACTORIALS[i-1] * i) % MOD;
  }
}

int64_t fast_choose(int n, int k) {
  if (k > n || k < 0)  return 0;
  int64_t numerator = FACTORIALS[n];
  int64_t denominator = (FACTORIALS[k] * FACTORIALS[n-k]) % MOD;
  return (numerator * modular_inverse(denominator)) % MOD;
}





void solve() {
  int n;
  cin >> n;
  vector<long> B(n+1);
  for (int i = 1; i <= n; i++)  cin >> B[i];
  // popcount[i] = number of 1s (out of n) in bit position 0...28
  vector<int> popcount(29, 0);

  // all n bits set
  for (int bit = 0; bit < 29; bit++) {
    if (B[n] & (1<<bit)) {
      popcount[bit] = n;
    }
  }

  for (int ct = n-1; ct >= 1; ct--) {
    long total = B[ct];
    for (int bit = 0; bit < 29; bit++) {
      if (popcount[bit] > ct) {
        // popcount[bit] choose ct extra
        total += 10LL*MOD;
        total -= (((1<<bit) * fast_choose(popcount[bit], ct)) % MOD);
        total %= MOD;
      }
    }
    total %= MOD;
    assert(total >= 0 && total < 536870912LL);
    for (int bit = 0; bit < 29; bit++) {
      if (total & (1<<bit)) {
        assert(popcount[bit] == 0);
        popcount[bit] = ct;
      }
    }
  }

  vector<int> answers(n, 0);
  for (int i = 0; i < n; i++) {
    for (int bit = 0; bit < 29; bit++) {
      // Set the bit in the first popcount[bit] numbers
      if (popcount[bit] > i) {
        answers[i] |= (1<<bit);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << answers[i] << " \n"[i == n-1];
  }

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init_factorials();

  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}