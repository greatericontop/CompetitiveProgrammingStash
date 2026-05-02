#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld, ", _x); \
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
int64_t modinv(int64_t a) {
  return mod_exp(a, MOD - 2);
}


void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<vector<int>>> segments_by_startloc(m+1);
  vector<long> failure_prob(m+1, 1);
  for (int i = 0; i < n; i++) {
    int l, r, p, q;
    cin >> l >> r >> p >> q;
    segments_by_startloc[l].push_back({l, r, p, q});
    long yes_chance = (p*modinv(q)) % MOD;
    long no_chance = (MOD + 1 - yes_chance) % MOD;
    failure_prob[l] = (failure_prob[l] * no_chance) % MOD;
  }
  vector<long> prefix_failure_prob(m+1);
  prefix_failure_prob[0] = 1;
  for (int i = 1; i <= m; i++) {
    prefix_failure_prob[i] = (prefix_failure_prob[i-1] * failure_prob[i]) % MOD;
  }
  PRINTVEC(failure_prob);
  PRINTVEC(prefix_failure_prob);

  vector<long> dp(m+2, 0);
  dp[m+1] = 1;  //100% chance of success once we reach this point
  for (int i = m; i >= 1; i--) {

    for (const auto& seg : segments_by_startloc[i]) {
      int l = seg[0], r = seg[1], p = seg[2], q = seg[3];
      fprintf(stderr, "  i=%d   consider segment [%d, %d] with p/q = %d/%d\n", i, l, r, p, q);
      long everyone_fails_chance = (prefix_failure_prob[r] * modinv(prefix_failure_prob[l-1])) % MOD;
      fprintf(stderr, "    everyone_fails_chance = %lld\n", everyone_fails_chance);
      long yes_chance = (p*modinv(q)) % MOD;
      long no_chance = (MOD + 1 - yes_chance) % MOD;
      // P(we get yes and everyone with left segment in our range gets no)
      long contrib = ((yes_chance * modinv(no_chance))%MOD) * everyone_fails_chance % MOD;
      // * dp
      contrib = (contrib * dp[r+1]) % MOD;
      fprintf(stderr, "    contrib = %lld\n", contrib);
      dp[i] = (dp[i] + contrib) % MOD;
    }

  }
  PRINTVEC(dp);

  cout << dp[1] << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
