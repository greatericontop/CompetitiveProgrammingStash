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
//constexpr static long MOD =   998'244'353LL;










void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n+1);
  FORI1(n)  cin >> a[i];

  vector<long> range_sum(n+1, 0);
  FORI1(n)  range_sum[i] = range_sum[i-1] + a[i];
  vector<int> range_xor(n+1, 0);
  FORI1(n)  range_xor[i] = range_xor[i-1] ^ a[i];

  // if the right endpoint is r, then for it to work we must have l <= closest_zero_xor[r]
  vector<int> closest_zero_xor(n+1, -1000);

  map<int, int> last_even_occ, last_odd_occ;
  //last_even_occ[0] = 0;  last_odd_occ[0] = 0;
  for (int i = 1; i <= n; i++) {
    int x = range_xor[i];
    if (i % 2 == 0) {
      if (last_odd_occ.count(x)) {
        closest_zero_xor[i] = last_odd_occ[x] + 1;
      }
      last_even_occ[x] = i;
    } else {
      if (last_even_occ.count(x)) {
        closest_zero_xor[i] = last_even_occ[x] + 1;
      }
      last_odd_occ[x] = i;
    }
  }
  PRINTVEC(closest_zero_xor);


  while (q --> 0) {
    int l, r;
    cin >> l >> r;
    if (range_sum[r] - range_sum[l-1] == 0) {
      cout << "0\n";
    } else if ((r - l + 1) % 2 == 0) {
      // even size
      if ((range_xor[r] ^ range_xor[l-1]) == 0) {
        if (a[l] == 0 || a[r] == 0) {
          cout << "1\n";
        } else if (l <= closest_zero_xor[r]) {
          cout << "2\n";
        } else {
          cout << "-1\n";
        }
      } else {
        cout << "-1\n";
      }
    } else {
      // odd size
      if ((range_xor[r] ^ range_xor[l-1]) == 0) {
        cout << "1\n";
      } else {
        cout << "-1\n";
      }
    }
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

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
