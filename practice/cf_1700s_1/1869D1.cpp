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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










constexpr static inline bool ispowerof2(long x) {
  return (x & (x - 1)) == 0;
}

void solve() {
  int n;
  cin >> n;
  vector<long> a(n);
  FORI(n)  cin >> a[i];
  long sum = accumulate(a.begin(), a.end(), 0LL);
  if (sum % n != 0) {
    cout << "NO\n";
    return;
  }
  long target = sum / n;

  multiset<long> in_degrees;
  multiset<long> out_degrees;
  bool at_least_one_starter = false;
  bool has_equals = false;
  bool only_equals = true;
  for (int i = 0; i < n; i++) {
    if (a[i] == target) {
      // don't need to add the edges
      at_least_one_starter = true;
      has_equals = true;
      continue;
    }
    only_equals = false;
    long difference = abs(a[i] - target);
    long big = 1;
    while (big <= difference)  big *= 2;
    long small = big - difference;
    if (!ispowerof2(small)) {
      fprintf(stderr, "not power of 2: %lld %lld\n", a[i], target);
      cout << "NO\n";
      return;
    }
    if (a[i] > target) {
      out_degrees.insert(big);
      in_degrees.insert(small);
      if (a[i] - big >= 0) {
        at_least_one_starter = true;
      }
    } else {
      out_degrees.insert(small);
      in_degrees.insert(big);
      if (a[i] - small >= 0) {
        at_least_one_starter = true;
      }
    }
  }

  if (!at_least_one_starter) {
    cout << "NO\n";
    return;
  }
  if (has_equals) {
    // we must be able to embed ourselves as the smallest in/out edge
    // or if all equals and n >= 2 then those form their own cycle
    if ((out_degrees.empty() || *out_degrees.begin() > target) && !(only_equals && n >= 2)) {
      cout << "NO\n";
      return;
    }
  }
  PRINTVECL(in_degrees);
  PRINTVECL(out_degrees);

  // check that the multisets are the same
  if (in_degrees != out_degrees) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
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
