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
  int n;
  cin >> n;
  vector<bool> a(n);
  FORI(n) {
    int x; cin >> x;
    if (x % 2 == 0)  a[i] = false;
    else  a[i] = true;
  }
  //PRINTVEC(a);

  long ans = 0;
  long c0 = 0, c1 = 0, c00 = 0, c01 = 0, c10 = 0, c11 = 0;

  for (bool x : a) {
    long c0_new = 0, c1_new = 0, c00_new = 0, c01_new = 0, c10_new = 0, c11_new = 0;
    if (x) {  // 1
      c1_new++;
      c01_new += c0;
      c11_new += c1;
      // 01 -> 011
      c11_new += c01;
      ans += c01;
      // 10 -> 101
      c01_new += c10;
      ans += c10;
    } else {  // 0
      c0_new++;
      c00_new += c0;
      c10_new += c1;
      // 00 -> 000
      c00_new += c00;
      ans += c00;
      // 11 -> 110
      c10_new += c11;
      ans += c11;
    }

    c0 += c0_new;
    c1 += c1_new;
    c00 += c00_new;
    c01 += c01_new;
    c10 += c10_new;
    c11 += c11_new;
    c0 %= MOD;
    c1 %= MOD;
    c00 %= MOD;
    c01 %= MOD;
    c10 %= MOD;
    c11 %= MOD;
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
