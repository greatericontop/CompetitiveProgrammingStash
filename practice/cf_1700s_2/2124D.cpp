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










void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<pairii> b(n);
  FORI(n)  b[i] = {a[i], i};
  sort(b.begin(), b.end());

  if (k == 1) {
    cout << "YES\n";
    return;
  }

  vector<int> small_indices;
  vector<int> border_indices;
  int border_x = b[k-2].first;
  for (int i = 0; i < n; i++) {
    if (a[i] < border_x)  small_indices.pb(i);
    else if (a[i] == border_x)  border_indices.pb(i);
  }

  PRINTVEC(small_indices);
  PRINTVEC(border_indices);

  // Check validity of small_indices
  int m = small_indices.size();
  if (m == 0) {
    // all first k-1 are the same number
    cout << "YES\n";
    return;
  }
  int i0 = (m-1)/2, j0 = (m)/2;
  int i = i0, j = j0;
  fprintf(stderr, "m: %d, i: %d, j: %d\n", m, i, j);
  int border_ct = 0;
  while (i >= 0 && j < m) {
    if (a[small_indices[i]] != a[small_indices[j]]) {
      cout << "NO\n";
      return;
    }

    int l1 = (i == 0) ? 0 : small_indices[i-1]+1;
    int l2 = small_indices[i]-1;
    int l_ct = 0;
    for (int p = l1; p <= l2; p++) {
      if (a[p] == border_x)  l_ct++;
    }
    int r1 = small_indices[j]+1;
    int r2 = (j == m-1) ? n-1 : small_indices[j+1]-1;
    int r_ct = 0;
    for (int p = r1; p <= r2; p++) {
      if (a[p] == border_x)  r_ct++;
    }
    border_ct += 2 * min(l_ct, r_ct);

    i--; j++;
  }

  int center_ct = 0;
  for (int p = small_indices[i0]+1; p <= small_indices[j0]-1; p++) {
    if (a[p] == border_x)  center_ct++;
  }

  int required_border_ct = (k - 1) - m;
  fprintf(stderr, "border_ct: %d, center_ct: %d, required_border_ct: %d\n", border_ct, center_ct, required_border_ct);
  if (border_ct + center_ct < required_border_ct) {
    cout << "NO\n";
    return;
  } else {
    cout << "YES\n";
    return;
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
