
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
  int n;
  cin >> n;
  vector<long> a(n);
  FORI(n)  cin >> a[i];

  vector<long> suffix_delta(n+1, 0);
  vector<long> suffix_extra_negative(n+1, 0);

  for (int i = n-1; i >= 0; i--) {
    long x = a[i];
    long delta = suffix_delta[i+1];
    long extra_negative = suffix_extra_negative[i+1];

    if (x >= 0) {
      long loss = max(0LL, min(x, extra_negative));
      x -= loss; extra_negative -= loss;
      delta += x;
    } else {
      long y = -x;
      extra_negative += y;
      // delta unchanged
    }

    suffix_delta[i] = delta;
    suffix_extra_negative[i] = extra_negative;
  }
  PRINTVECL(suffix_delta);
  PRINTVECL(suffix_extra_negative);


  long best = suffix_delta[0];  //set floor initially
  long which_k = 0;
  long running_total = 0;
  for (int i = 0; i < n; i++) {
    // set floor right after a[i]
    running_total += a[i];
    long delta = suffix_delta[i+1];
    fprintf(stderr, "answer for cut after i=%d, %lld\n", i, running_total + delta);
    long score = running_total + delta;
    if (score > best) {
      best = score;
      which_k = running_total;
    }
  }

  cout << which_k << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
