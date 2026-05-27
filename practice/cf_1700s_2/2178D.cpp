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
  int n, m;
  cin >> n >> m;
  vector<pairii> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i+1;
  }
  sort(a.begin(), a.end());

  if (m > n/2) {
    cout << -1 << "\n";
    return;
  }

  vector<pairii> ans;

  if (m == 0) {
    int highest_health = a[n-1].first;
    int i = 0;
    while (i < n-1 && a[i].first < highest_health) {
      highest_health -= a[i].first;
      i++;
    }
    if (i == n-1) {
      cout << -1 << "\n";
      return;
    } else {
      for (int j = 0; j < i; j++) {
        ans.pb({a[j].second, a[n-1].second});
      }
      for (; i < n-1; i++) {
        ans.pb({a[i].second, a[i+1].second});
      }
    }

  } else {

    // Get rid of: 0 ... n-2m-1
    // Final half:  n-m ... n-1

    for (int i = 0; i <= n-2*m-1; i++) {
      // elf 1 attacks elf 2, elf 1 dies
      ans.pb({a[i].second, a[i+1].second});
    }
    for (int i = 0; i < m; i++) {
      ans.pb({a[n-m+i].second, a[n-2*m+i].second});
    }

  }



  cout << ans.size() << "\n";
  for (const auto& p : ans) {
    cout << p.first << " " << p.second << "\n";
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
