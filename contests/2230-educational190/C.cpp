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
  int n;
  cin >> n;
  vector<long> c(n);
  for (int i = 0; i < n; i++)  cin >> c[i];
  long num_cards_above_2 = 0;
  long num_cards_unique = 0;
  long num_types_above_2 = 0;
  for (int i = 0; i < n; i++) {
    if (c[i] >= 2) {
      num_cards_above_2 += c[i];
      num_types_above_2++;
    } else {
      num_cards_unique += c[i];
    }
  }

  long total_cards = num_cards_above_2 + num_cards_unique;
  if (total_cards < 3) {
    cout << 0 << "\n";
    return;
  }

  if (num_cards_above_2 < 2) {
    fprintf(stderr, "special case: all cards unique\n");
    cout << "0\n";
    return;
  } else if (num_types_above_2 == 1) {
    fprintf(stderr, "special case: only 1 chain\n");
    long max_unique = num_cards_above_2 / 2;
    long ans = min(max_unique, num_cards_unique) + num_cards_above_2;
    cout << ans << "\n";
  } else {
    long max_unique = 0;
    for (int i = 0; i < n; i++) {
      if (c[i] >= 2) {
        max_unique += (c[i]-2) / 2;
      }
    }
    long ans = min(max_unique, num_cards_unique) + num_cards_above_2;
    cout << ans << "\n";
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
