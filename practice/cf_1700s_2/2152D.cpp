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
  int n, q;
  cin >> n >> q;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  vector<int> turns_required(n+1);
  vector<int> is_borderline(n+1);
  for (int i = 1; i <= n; i++) {
    int t = 1;
    while ((1<<t)+1 < a[i])  t++;
    turns_required[i] = t;
    if ((1<<t)+1 == a[i])  is_borderline[i] = 1;
    else  is_borderline[i] = 0;
  }
  vector<int> turns_required_prefix(n+1, 0);
  for (int i = 1; i <= n; i++)  turns_required_prefix[i] = turns_required_prefix[i-1] + turns_required[i];
  vector<int> borderline_prefix(n+1, 0);
  for (int i = 1; i <= n; i++)  borderline_prefix[i] = borderline_prefix[i-1] + is_borderline[i];

  while (q --> 0) {
    int l, r;
    cin >> l >> r;
    int turns = turns_required_prefix[r] - turns_required_prefix[l-1];
    int borderline = borderline_prefix[r] - borderline_prefix[l-1];
    cout << (turns + borderline/2) << "\n";
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
