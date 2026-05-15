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









int calc_first_one(const vector<int>& a, const set<int>& one_indices) {
  if (one_indices.empty())  return INT(1e8);
  int first = *one_indices.begin();
  int last = *one_indices.rbegin();
  return min(first-1, INT(a.size())-1-last);
}


void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n+1, 0);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  set<int> one_indices;
  for (int i = 1; i <= n; i++) {
    if (a[i] == 1)  one_indices.insert(i);
  }
  int totalsum = accumulate(a.begin(), a.end(), 0);

  while (q--) {
    int op; cin >> op;
    if (op == 1) {
      int s; cin >> s;
      int targ = totalsum - s;
      int first_one = calc_first_one(a, one_indices);
      fprintf(stderr, "targ = %d, first one = %d\n", targ, first_one);
      if (targ < 0) {
        cout << "NO\n";
      } else if (targ >= 2*first_one || targ % 2 == 0) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    } else {
      int i, v; cin >> i >> v;
      if (a[i] == 1)  one_indices.erase(i);
      totalsum -= a[i];
      a[i] = v;
      if (a[i] == 1)  one_indices.insert(i);
      totalsum += a[i];
      fprintf(stderr, "after update: totalsum = %d, first one = %d\n", totalsum, calc_first_one(a, one_indices));
      PRINTVEC(a);
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
