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









struct Operation {
  int which_disk;
  int from;
  int to;
};

/*
 * Kentq orz recursive spec: solves n disks from :from: to :to: using :extra:
 *   in 2^(n-1) - 1 moves or less.
 *   Base case: n = 1 in 1 move (trivial)
 */
void solve_recursively(int n, const vector<int>& h, int from, int to, int extra, vector<Operation>& ops) {
  if (n == 0) {
    return;
  }
  if (n == 1) {
    ops.push_back({1, from, to});
    return;
  }

  int m = h[n];
  if (m == n - 1) {
    solve_recursively(n-1, h, from, extra, to, ops);
    ops.push_back({n, from, to});
    solve_recursively(n-1, h, extra, to, from, ops);
  } else {
    solve_recursively(m, h, from, extra, to, ops);
    ops.push_back({n, from, to});
    solve_recursively(m, h, extra, from, to, ops);
    solve_recursively(n-1, h, from, to, extra, ops);
  }
}


void solve() {
  int n;
  cin >> n;
  vector<int> a(n+1);
  FORI1(n)  cin >> a[i];
  vector<int> h(n+1);
  for (int i = 1; i <= n; i++) {
    h[i] = (i-1) - a[i];
    if (h[i] < 0) {
      cout << "NO\n";
      return;
    }
  }

  // If heights are valid, then the answer is yes
  vector<Operation> ops;
  solve_recursively(n, h, 1, 3, 2, ops);
  assert(ops.size() <= (1 << n));
  cout << "YES\n";
  cout << ops.size() << "\n";
  for (const auto& op : ops) {
    cout << op.which_disk << " " << op.from << " " << op.to << "\n";
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
