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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;
constexpr static uint64_t MOD = 5'000'000'000'000'000'000ULL;










void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> arrs(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> arrs[i][j];
    }
  }
  // .first = statistic, .second = index (0-based) of the array
  vector<pair<uint64_t, int>> statistics(n);
  for (int a = 0; a < n; a++) {
    uint64_t stat = 0;
    for (int j = 0; j < m; j++) {
      stat += ((uint64_t) arrs[a][j]) * ((uint64_t) j);
      stat %= MOD;
    }
    statistics[a] = {stat, a};
  }
  sort(statistics.begin(), statistics.end());

  uint64_t standard, special; int special_idx;
  if (statistics[0].first == statistics[1].first) {
    for (int i = 0; i < n-2; i++)  assert(statistics[i].first == statistics[i+1].first);
    // special is back
    standard = statistics[0].first;
    special = statistics[n-1].first;
    special_idx = statistics[n-1].second;
  } else {
    // special is front
    for (int i = 1; i < n-1; i++)  assert(statistics[i].first == statistics[i+1].first);
    standard = statistics[n-1].first;
    special = statistics[0].first;
    special_idx = statistics[0].second;
  }

  uint64_t diff = (special - standard + MOD) % MOD;
  assert(diff <= ((uint64_t)2e18));

  cout << special_idx + 1 << " " << diff << "\n";

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
