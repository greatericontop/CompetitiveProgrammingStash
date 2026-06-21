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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  int true_zero_count = 0;
  vector<int> cur;  cur.reserve(n);
  for (int x : a) {
    if (x == 0) {
      true_zero_count++;
    } else {
      cur.pb(x);
    }
  }
  int pending_zero_count = 0;

  // naive simulation is sufficient to pass
  // O(unique log unique), but sum of unique is bounded to like 1 million
  while (true) {
    PRINTVEC(cur);
    fprintf(stderr, "true zero %d, pending zero %d\n", true_zero_count, pending_zero_count);
    if (cur.empty()) {
      cout << 0 << "\n";
      return;
    }
    if (cur.size() == 1) {
      if (true_zero_count == 0 && pending_zero_count > 0) {
        // meaning we have multiple of a single element
        cout << 0 << "\n";
        return;
      }
      cout << cur[0] << "\n";
      return;
    }

    set<int> seen;
    int new_true_zero_count = max(true_zero_count-1, 0) + pending_zero_count;
    pending_zero_count = 0;
    if (true_zero_count > 0) { // NOT pending
      seen.insert(cur[0]);
    }
    for (int i = 1; i < INT(cur.size()); i++) {
      int diff = cur[i] - cur[i-1];
      if (seen.count(diff)) {
        pending_zero_count++;
      } else {
        seen.insert(diff);
      }
    }

    cur.clear();
    for (int x : seen) {
      cur.pb(x);
    }
    true_zero_count = new_true_zero_count;
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

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
