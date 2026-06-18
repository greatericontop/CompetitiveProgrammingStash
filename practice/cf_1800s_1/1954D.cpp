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
//constexpr static long MOD = 1'000'000'007LL;
constexpr static long MOD =   998'244'353LL;









struct State {
  long number;
  long sum;
  long odd_ct;
};


long over2(long x) {
  if (x % 2 == 0)  return x / 2;
  return (x + MOD) / 2;
}


void solve() {
  int n;
  cin >> n;
  vector<int> a(n+1);
  FORI1(n)  cin >> a[i];
  sort(a.begin()+1, a.end());

  vector<State> dp(5001, {0, 0, 0});
  for (int i = n; i >= 1; i--) {
    vector<State> dp_new(5001, {0, 0, 0});
    dp_new[a[i]].number += 1;
    dp_new[a[i]].sum += a[i];
    dp_new[a[i]].odd_ct += (a[i] % 2);
    dp_new[a[i]].number %= MOD; dp_new[a[i]].sum %= MOD; dp_new[a[i]].odd_ct %= MOD;

    for (int j = 0; j <= 5000; j++) {
      // dp[j] -> add a[i] to it -> dp_new[new_j]
      // new skew is reduced by a[i]
      int new_j = max(0, j - a[i]);

      dp_new[new_j].number += dp[j].number;
      dp_new[new_j].number %= MOD;

      dp_new[new_j].sum += dp[j].sum + dp[j].number*a[i];
      dp_new[new_j].sum %= MOD;

      if (a[i] % 2 == 0) {
        dp_new[new_j].odd_ct += dp[j].odd_ct;
        dp_new[new_j].odd_ct %= MOD;
      } else {
        dp_new[new_j].odd_ct += MOD + dp[j].number - dp[j].odd_ct;  //even ones are the new odd ones
        dp_new[new_j].odd_ct %= MOD;
      }
    }

    for (int j = 0; j <= 5000; j++) {
      dp[j].number += dp_new[j].number;
      dp[j].number %= MOD;
      dp[j].sum += dp_new[j].sum;
      dp[j].sum %= MOD;
      dp[j].odd_ct += dp_new[j].odd_ct;
      dp[j].odd_ct %= MOD;
    }
  }

  for (int i = 0; i <= 5; i++) {
    fprintf(stderr, "skew %d: number %lld, sum %lld, odd_ct %lld\n", i, dp[i].number, dp[i].sum, dp[i].odd_ct);
  }

  long ans = 0;
  for (int extra = 0; extra <= 5000; extra++) {
    // total ceil(sum/2)
    long adjusted_sum = (MOD + dp[extra].sum - dp[extra].odd_ct) % MOD;
    ans += over2(adjusted_sum);
    ans += dp[extra].odd_ct;
    ans %= MOD;
    ans += (extra/2) * dp[extra].number;
    ans %= MOD;
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

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
