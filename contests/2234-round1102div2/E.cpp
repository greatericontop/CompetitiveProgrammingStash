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









long FACTORIALS[600001];
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

long solve_rec(int l, int r, const vector<long>& a) {
  int min_i = -2;
  for (int d = 0; d <= (r - l + 1)/2; d++) {
    int j = l + d;
    long expected_if_min;
    if (j >= l && j <= r) {
      expected_if_min = (r - j + 1) * (j - l + 1);
      if (a[j] == expected_if_min) {
        min_i = j;
        break;
      } else if (a[j] > expected_if_min) {
        fprintf(stderr, "[%d %d] contradiction while min finding\n", l, r);
        return -1;  //contradiction
      }
    }
    j = r - d;
    if (j >= l && j <= r) {
      expected_if_min = (r - j + 1) * (j - l + 1);
      if (a[j] == expected_if_min) {
        min_i = j;
        break;
      } else if (a[j] > expected_if_min) {
        fprintf(stderr, "[%d %d] contradiction while min finding\n", l, r);
        return -1;
      }
    }
  }
  if (min_i == -2) {
    return -1;
  }
  fprintf(stderr, "found min at index %d\n", min_i);

  if (l == r) {
    //assuming prev checks passed
    return 1;
  }
  if (l == min_i) {
    return solve_rec(l+1, r, a);
  } else if (r == min_i) {
    return solve_rec(l, r-1, a);
  } else {
    long ans1 = solve_rec(l, min_i-1, a);
    long ans2 = solve_rec(min_i+1, r, a);
    if (ans1 == -1 || ans2 == -1) {
      fprintf(stderr, "[%d %d] contradiction in subarray\n", l, r);
      return -1;
    }
    int size1 = min_i - l;
    int size2 = r - min_i;
    // we can interpolate
    long multiplier = FACTORIALS[size1+size2];
    multiplier *= modular_inverse(FACTORIALS[size1]);
    multiplier %= MOD;
    multiplier *= modular_inverse(FACTORIALS[size2]);
    multiplier %= MOD;
    return (((multiplier * ans1) % MOD) * ans2) % MOD;
  }


}


void solve() {
  int n;
  cin >> n;
  vector<long> a(n);
  FORI(n)  cin >> a[i];

  long ans = solve_rec(0, n-1, a);
  if (ans == -1) {
    ans = 0;
  }
  cout << ans << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  FACTORIALS[0] = 1;
  for (int i = 1; i <= 600000; i++) {
    FACTORIALS[i] = (FACTORIALS[i-1] * i) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
