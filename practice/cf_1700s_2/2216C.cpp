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
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }










void solve() {
  int n, k, small, large;
  cin >> n >> k >> small >> large;
  if (large < small)  swap(small, large);
  vector<long> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];

  vector<long> mod_small(n+1), mod_big(n+1), opt(n+1);
  for (int i = 1; i <= n; i++) {
    mod_small[i] = a[i] % small;
    mod_big[i] = (a[i] % large) % small;
    opt[i] = min(mod_small[i], mod_big[i]);
  }
  vector<long> mod_small_prefix(n+1, 0), mod_big_prefix(n+1, 0), opt_prefix(n+1, 0);
  for (int i = 1; i <= n; i++) {
    mod_small_prefix[i] = mod_small_prefix[i-1] + mod_small[i];
    mod_big_prefix[i] = mod_big_prefix[i-1] + mod_big[i];
    opt_prefix[i] = opt_prefix[i-1] + opt[i];
  }


  long bestans = LONG(1e18);
  for (int left = 1; left <= n-k+1; left++) {
    int right = left + k - 1;

    long ans1 = opt_prefix[left-1] + (mod_small_prefix[right] - mod_small_prefix[left-1]) + (opt_prefix[n] - opt_prefix[right]);
    long ans2 = opt_prefix[left-1] + (mod_big_prefix[right] - mod_big_prefix[left-1]) + (opt_prefix[n] - opt_prefix[right]);
    bestans = min(bestans, min(ans1, ans2));
  }

  cout << bestans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
