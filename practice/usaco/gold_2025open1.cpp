#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





constexpr static long MOD = 1'000'000'007LL;

/* O(log exp) */
int64_t mod_exp(int64_t base, int64_t exp) {
  assert(base >= 0 && base < MOD);
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
  assert(a >= 0 && a < MOD);
  return mod_exp(a, MOD - 2);
}

long FACTORIALS[1'000'200];
void init_factorials() {
  FACTORIALS[0] = 1;
  for (int i = 1; i <= 1'000'100; i++) {
    FACTORIALS[i] = (FACTORIALS[i-1] * i) % MOD;
  }
}





void solve() {
  int k;
  long n, l;
  cin >> k >> n >> l;
  string s;
  cin >> s;

  // Sanity checks
  int m_ct = 0;
  int o_ct = 0;
  for (char c : s) {
    if (c == 'M')  m_ct++;
    else if (c == 'O')  o_ct++;
    else  assert(false);
  }
  assert(m_ct * k == o_ct);
  assert(s.front() == 'M');
  assert(s.back() == 'O');


  vector<int> compressed_string;
  char cur = '\0';
  for (int i = n-1; i >= 0; i--) {
    if (s[i] == cur) {
      compressed_string.back()++;
    } else {
      compressed_string.push_back(1);
      cur = s[i];
    }
  }
  assert(compressed_string.size() % 2 == 0);
  fprintf(stderr, "compressed_string = ");
  for (int x : compressed_string) {
    fprintf(stderr, "%d ", x);
  }
  fprintf(stderr, "\n");

  long total = 1;
  int o = 0;
  for (int i = 0; i < compressed_string.size(); i += 2) {
    int j = i+1;
    o += compressed_string[i];
    int m = compressed_string[j];

    // o choose (k, k, k, k xm, o-k*m)
    total *= FACTORIALS[o];
    total %= MOD;
    total = (total * modular_inverse(mod_exp(FACTORIALS[k], m))) % MOD;
    assert(o - k*m >= 0);
    total = (total * modular_inverse(FACTORIALS[o - k*m])) % MOD;
    total %= MOD;
    fprintf(stderr, "total = %lld", total);

    o -= k*m;
  }
  assert(o == 0);

  long ans = mod_exp(total, l);
  cout << ans << "\n";
}





int main() {
  init_factorials();
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}