#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "[%d %d %d %d], ", _x[0], _x[1], _x[2], _x[3]); \
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
  vector<vector<int>> events;
  for (int i = 0; i < n; i++) {
    int l, r, p, q;
    cin >> l >> r >> p >> q;
    events.push_back({l, 1, p, q});
    events.push_back({r+1, 2, p, q});
  }
  sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
    return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
  });
  PRINTVEC(events);

  long fracsum = 0;
  long product = 1;
  int ptr = 0;
  for (int i = 1; i <= m; i++) {
    while (ptr < events.size() && events[ptr][0] == i) {
      int type = events[ptr][1];
      long p = events[ptr][2];
      long q = events[ptr][3];
      long yes_chance = (p*modinv(q)) % MOD;
      long no_chance = (998244353 - yes_chance) % MOD;
      long f = (yes_chance * modinv(no_chance)) % MOD;
      if (type == 1) {
        // new event
        fracsum = (fracsum + f) % MOD;
        product = (product * no_chance) % MOD;
      } else {
        fracsum = (fracsum - f + MOD) % MOD;
        product = (product * modinv(no_chance)) % MOD;
      }
      ptr++;
    }
    long ans = (fracsum * product) % MOD;
    cout << ans << "\n";
  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
