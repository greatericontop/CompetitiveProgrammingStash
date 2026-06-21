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










void solve() {
  int n;
  cin >> n;
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];
  int q;
  cin >> q;
  vector<long> queries(q);
  FORI(q)  cin >> queries[i];

  vector<long> prefix_sum(n+1, 0);
  FORI1(n)  prefix_sum[i] = prefix_sum[i-1] + a[i];

  vector<long> time_to_fill_i(n+1, 0);
  for (int i = 1; i <= n; i++) {
    time_to_fill_i[i] = ceildivl(prefix_sum[i], i);
  }
  vector<long> time_to_fill_i_rmq(n+1, 0);
  FORI1(n)  time_to_fill_i_rmq[i] = max(time_to_fill_i_rmq[i-1], time_to_fill_i[i]);

  vector<long> pipe_count_to_time(n+1, LLONG_MAX);
  for (int i = 1; i <= n; i++) {
    pipe_count_to_time[i] = max(time_to_fill_i_rmq[i], ceildivl(prefix_sum[n], i));
    assert(pipe_count_to_time[i] <= pipe_count_to_time[i-1]);
  }

  PRINTVECL(pipe_count_to_time);

  for (int time_required : queries) {
    auto it = lower_bound(pipe_count_to_time.begin(), pipe_count_to_time.end(), time_required, greater<long>());
    if (it == pipe_count_to_time.end()) {
      cout << -1 << "\n";
    } else {
      cout << distance(pipe_count_to_time.begin(), it) << "\n";
    }
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

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
