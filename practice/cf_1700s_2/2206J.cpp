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









void subtractans(long& ans, const vector<int>& p_rev, int n, int i) {
  if (i < n) {
    ans -= (p_rev[i+1] - p_rev[i] + n - 1) % n;
  }
  if (i >= 1) {
    ans -= (p_rev[i] - p_rev[i-1] + n - 1) % n;
  }
}
void addans(long& ans, const vector<int>& p_rev, int n, int i) {
  if (i < n) {
    ans += (p_rev[i+1] - p_rev[i] + n - 1) % n;
  }
  if (i >= 1) {
    ans += (p_rev[i] - p_rev[i-1] + n - 1) % n;
  }
}


void solve() {
  int n, d;
  cin >> n >> d;
  vector<int> a(n+1);
  vector<int> a_rev(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a_rev[a[i]] = i;
  }
  vector<int> b(n+1);
  vector<int> b_rev(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    b_rev[b[i]] = i;
  }

  vector<int> p_rev(n+1);
  for (int i = 1; i <= n; i++) {
    p_rev[i] = a_rev[b[i]];
  }
  long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += (p_rev[i+1] - p_rev[i] + n - 1) % n;
  }

  PRINTVEC(p_rev);
  cout << ans << "\n";

  while (d --> 1) {
    int c, x, y;
    cin >> c >> x >> y;

    if (c == 2) {
      if (x > y)  swap(x, y);
      // swap b_x, b_y
      // aka swap p_rev[x], p_rev[y]
      subtractans(ans, p_rev, n, x);
      subtractans(ans, p_rev, n, y);
      if (x+1 == y)  ans += (p_rev[y] - p_rev[x] + n - 1) % n;
      swap(b[x], b[y]);
      swap(b_rev[b[x]], b_rev[b[y]]);
      swap(p_rev[x], p_rev[y]);
      addans(ans, p_rev, n, x);
      addans(ans, p_rev, n, y);
      if (x+1 == y)  ans -= (p_rev[y] - p_rev[x] + n - 1) % n;
    } else {
      // swap a_x, a_y
      // swap a_rev[a_x], a_rev[a_y]
      // swap p_rev of b_inv[a[x]] and b_inv[a[y]]
      int i = b_rev[a[x]];
      int j = b_rev[a[y]];
      if (i > j)  swap(i, j);
      subtractans(ans, p_rev, n, i);
      subtractans(ans, p_rev, n, j);
      if (i+1 == j)  ans += (p_rev[j] - p_rev[i] + n - 1) % n;
      fprintf(stderr, "after subtracting, ans = %d\n", ans);
      swap(a[x], a[y]);
      swap(a_rev[a[x]], a_rev[a[y]]);
      swap(p_rev[i], p_rev[j]);
      addans(ans, p_rev, n, i);
      addans(ans, p_rev, n, j);
      if (i+1 == j)  ans -= (p_rev[j] - p_rev[i] + n - 1) % n;
    }

    PRINTVEC(p_rev);
    cout << ans << "\n";
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
