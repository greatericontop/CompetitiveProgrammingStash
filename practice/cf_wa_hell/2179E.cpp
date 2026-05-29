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
  long x, y;
  cin >> n >> x >> y;
  string s;
  cin >> s;
  vector<long> p(n);
  FORI(n)  cin >> p[i];


  bool is_s_pure = true;
  for (int i = 1; i < n; i++) {
    if (s[i] != s[i - 1]) {
      is_s_pure = false;
      break;
    }
  }

  if (!is_s_pure) {
    // At least one district won by x/0, one district won by y/1.
    long required_a = 0, required_b = 0, required_total = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '0') {
        required_a += p[i]/2 + 1;
      } else {
        required_b += p[i]/2 + 1;
      }
      required_total += p[i];
    }
    if (x >= required_a && y >= required_b && x + y >= required_total) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }


  } else {
    // One candidate wins all districts
    if (s[0] == '1') {
      swap(x, y);
    }


    long required_a = 0, required_either = 0;
    long even_ps = 0;
    for (int i = 0; i < n; i++) {
      if (p[i] % 2 == 0) {
        even_ps++;
      }
      required_a += p[i]/2 + 1;
      required_either += p[i] - (p[i]/2 + 1);
    }

    if (x >= required_a && x + y - required_a >= required_either) {
      long x_left = x - required_a;
      long y_left = y - required_either;
      fprintf(stderr, "x_left: %lld, y_left: %lld, even_ps: %lld\n", x_left, y_left, even_ps);
      if (x_left >= y_left - even_ps) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    } else {
      cout << "NO\n";
    }




  }


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
