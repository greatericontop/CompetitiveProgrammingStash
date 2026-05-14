#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECL(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:   ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECP(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%d %d],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECPL(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%lld %lld],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










#define BITS 30
struct PrefixXorSum {
  int zero_bit_ct[BITS];
  int one_bit_ct[BITS];

  PrefixXorSum() {
    memset(zero_bit_ct, 0, sizeof(zero_bit_ct));
    memset(one_bit_ct, 0, sizeof(one_bit_ct));
  }

  long calculate() const {
    long x = 0;
    for (int b = 0; b < BITS; b++) {
      x += LONG(one_bit_ct[b]) * LONG(1LL<<b);
    }
    return x;
  }

  PrefixXorSum extend(long x) const {
    PrefixXorSum ret;
    // xor all existing sums
    for (int b = 0; b < BITS; b++) {
      if (x & (1<<b)) {
        // swap
        ret.zero_bit_ct[b] = one_bit_ct[b];
        ret.one_bit_ct[b] = zero_bit_ct[b];
      } else {
        ret.zero_bit_ct[b] = zero_bit_ct[b];
        ret.one_bit_ct[b] = one_bit_ct[b];
      }
    }
    // add x
    for (int b = 0; b < BITS; b++) {
      if (x & (1<<b)) {
        ret.one_bit_ct[b]++;
      } else {
        ret.zero_bit_ct[b]++;
      }
    }
    return ret;
  }

  void debug() {
    for (int b = 0; b < BITS; b++) {
      fprintf(stderr, "b=%d: 0 x%d 1 x%d\n", b, zero_bit_ct[b], one_bit_ct[b]);
    }
  }
};


constexpr static long MOD = 998244353;


void solve() {
  int n;
  cin >> n;
  vector<long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<PrefixXorSum> prefix_xor_sums(n);
  prefix_xor_sums[0] = PrefixXorSum().extend(a[0]);
  for (int i = 1; i < n; i++) {
    prefix_xor_sums[i] = prefix_xor_sums[i-1].extend(a[i]);
  }
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "prefix_xor_sums[%d]:\n", i);
    prefix_xor_sums[i].debug();
    fprintf(stderr, "= %lld\n", prefix_xor_sums[i].calculate());
  }
  vector<PrefixXorSum> suffix_xor_sums(n);
  suffix_xor_sums[n-1] = PrefixXorSum().extend(a[n-1]);
  for (int i = n-2; i >= 0; i--) {
    suffix_xor_sums[i] = suffix_xor_sums[i+1].extend(a[i]);
  }
  // Those objects store the calculate() for all that END specifically at an index
  vector<long> pref(n);
  pref[0] = prefix_xor_sums[0].calculate();
  for (int i = 1; i < n; i++) {
    pref[i] = pref[i-1] + prefix_xor_sums[i].calculate();
    pref[i] %= MOD;
  }
  vector<long> suff(n);
  suff[n-1] = suffix_xor_sums[n-1].calculate();
  for (int i = n-2; i >= 0; i--) {
    suff[i] = suff[i+1] + suffix_xor_sums[i].calculate();
    suff[i] %= MOD;
  }
  PRINTVECL(pref);
  PRINTVECL(suff);

  long total_sum = pref[n-1];
  assert(suff[0] == pref[n-1]);
  long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += total_sum;
    ans %= MOD;
    if (i > 0) {
      ans -= pref[i-1];
      ans += 10*MOD;
      ans %= MOD;
    }
    if (i < n-1) {
      ans -= suff[i+1];
      ans += 10*MOD;
      ans %= MOD;
    }
  }

  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
