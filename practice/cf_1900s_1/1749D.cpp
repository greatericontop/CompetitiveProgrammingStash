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










void solve() {
  int n; long m;
  cin >> n >> m;

  int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  set<int> PRIMESET;  for (int p : PRIMES)  PRIMESET.insert(p);
  vector<long> prime_lcms(41);
  prime_lcms[2] = 2;
  for (int i = 3; i <= 40; i++) {
    long lcm_here = prime_lcms[i-1] * (PRIMESET.count(i) ? i : 1);
    prime_lcms[i] = lcm_here;
  }
  PRINTVECL(prime_lcms);

  long ok_running_total = 0;
  long pending = m % MOD, ok = 0;
  for (int i = 2; i <= n; i++) {
    // all ok arrays can have any elt added
    ok *= (m % MOD);
    ok %= MOD;
    long currently_pending = pending;
    long num_pending_x;
    if (i >= 40)  num_pending_x = 0;
    else  num_pending_x = m / prime_lcms[i];
    pending = currently_pending * (num_pending_x % MOD);
    pending %= MOD;
    ok += currently_pending * ((m - num_pending_x) % MOD);
    ok %= MOD;

    if (i >= 50)  assert(pending == 0);

    ok_running_total += ok;
    ok_running_total %= MOD;
  }

  cout << ok_running_total << "\n";

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
