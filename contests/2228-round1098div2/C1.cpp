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
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }








long calcnumformask(long mask, int msb, int digits[2]) {
  long x = 0;
  for (int bit = msb; bit >= 0; bit--) {
    x *= 10;
    x += digits[(mask >> bit) & 1];
  }
  return x;
}

void solve() {
  long a; int n;
  cin >> a >> n;
  assert(n == 2);
  int digits[2];
  FORI(2)  cin >> digits[i];

  int numdigitsina = 0;
  long temp = a;
  while (temp > 0) {
    temp /= 10;
    numdigitsina++;
  }
  if (numdigitsina == 0)  numdigitsina = 1;

  // find first num >= a
  long l = 0, r = (1<<numdigitsina)-1;
  while (l < r) {
    long mask = l + (r-l)/2;
    long x = calcnumformask(mask, numdigitsina-1, digits);
    fprintf(stderr, "number %lld for mask %lld\n", x, mask);
    if (x < a) {
      l = mask+1;
    } else {
      // x >= a
      r = mask;
    }
  }

  fprintf(stderr, "ended with masks %lld, %lld\n", l, l-1);
  long x1 = calcnumformask(l == 0 ? 0 : l-1, numdigitsina-1, digits);
  long x2 = calcnumformask(l, numdigitsina-1, digits);
  fprintf(stderr, "numbers %lld, %lld\n", x1, x2);

  // x3: with one less digit
  long x3 = 0;
  for (int i = 0; i < numdigitsina-1; i++) {
    x3 *= 10;
    x3 += digits[1];
  }
  if (x3 == 0 && digits[0] != 0) {
    x3 = LONG(2e18);
  }
  fprintf(stderr, "number with one less digit: %lld\n", x3);
  long x4 = 0;
  for (int i = 0; i < numdigitsina+1; i++) {
    x4 *= 10;
    x4 += (i == 0 && digits[0] == 0) ? digits[1] : digits[0];
  }
  fprintf(stderr, "number with one more digit: %lld\n", x4);

  long ans = min(min(min(abs(x1-a), abs(x2-a)), abs(x3-a)), abs(x4-a));
  cout << ans << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
