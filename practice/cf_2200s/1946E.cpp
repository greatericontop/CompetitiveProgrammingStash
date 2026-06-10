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
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









long FACTORIALS[200020];
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


/* Calc number of ways for the subarray until (NOT including) maxes[i] (initial call should be maxes[back] = absolute max */
long calcways(const vector<int>& maxes, int i) {
  if (i == 0) {
    // abs max is already placed here
    return 1;
  }
  if (i == 1) {
    // can arbitrarily order elements at positions 2...maxes[i]-1
    return FACTORIALS[maxes[i]-2];
  }

  int i_new = i - 1;
  long ways_left = calcways(maxes, i_new);

  // x choose (maxes[j]-1)
  int x = maxes[i]-2;
  int y = maxes[i_new]-1;
  long ch = FACTORIALS[x];
  ch *= modular_inverse(FACTORIALS[y]);
  ch %= MOD;
  ch *= ways_left;
  return ch % MOD;
}


void solve() {
  int n, prefcount, suffcount;
  cin >> n >> prefcount >> suffcount;
  vector<int> pref(prefcount), suff(suffcount);
  FORI(prefcount)  cin >> pref[i];
  FORI(suffcount)  cin >> suff[i];
  if (pref[0] != 1) {
    cout << "0\n";
    return;
  }
  if (suff[suffcount - 1] != n) {
    cout << "0\n";
    return;
  }
  if (pref.back() != suff.front()) {
    cout << "0\n";
    return;
  }
  if (n == 1) {
    cout << "1\n";
    return;
  }
  long pref_ways = calcways(pref, prefcount-1);
  fprintf(stderr, "prefix ways: %lld", pref_ways);

  for (int i = 0; i < suffcount; i++) {
    suff[i] = n + 1 - suff[i];
  }
  reverse(suff.begin(), suff.end());
  long suff_ways = calcways(suff, suffcount-1);
  fprintf(stderr, "suffix ways: %lld", suff_ways);

  // both ways: (n-1) choose (index of abs max - 1)
  long ans = FACTORIALS[n-1];
  ans *= modular_inverse(FACTORIALS[pref.back() - 1]);
  ans %= MOD;
  ans *= modular_inverse(FACTORIALS[n - pref.back()]);
  ans %= MOD;
  ans *= pref_ways;
  ans %= MOD;
  ans *= suff_ways;
  ans %= MOD;

  cout << ans << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  FACTORIALS[0] = 1;
  for (int i = 1; i <= 200010; i++) {
    FACTORIALS[i] = FACTORIALS[i - 1] * i;
    FACTORIALS[i] %= MOD;
  }

  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
