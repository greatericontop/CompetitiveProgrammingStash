#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


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
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }









constexpr static long MOD = 998244353LL;

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

long FACTORIALS[600'010];


void solve() {
  vector<int> chars(26);
  for (int i = 0; i < 26; i++)  cin >> chars[i];
  int n = accumulate(chars.begin(), chars.end(), 0);
  int target = n/2;
  int target2 = ceildiv(n, 2);
  long initial_ans = (FACTORIALS[target] * FACTORIALS[target2]) % MOD;
  for (int ci : chars) {
    initial_ans = (initial_ans * modular_inverse(FACTORIALS[ci])) % MOD;
  }

  // now count number of ways to get to target
  vector<long> dp(target+1);
  dp[0] = 1;

  for (int ci : chars) {
    if (ci == 0)  continue;
    vector<long> dp_new(dp);
    for (int j = 0; j <= target-ci; j++) {
      dp_new[j+ci] = (dp_new[j+ci] + dp[j]) % MOD;
    }
    swap(dp, dp_new);
  }

  long ans = (initial_ans * dp[target]) % MOD;
  cout << ans << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  FACTORIALS[0] = 1;
  for (int i = 1; i <= 600000; i++) {
    FACTORIALS[i] = (FACTORIALS[i - 1] * i) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
