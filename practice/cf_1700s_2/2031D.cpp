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









void solve_recursively(vector<int>& a, int n, set<pairii>& indices, vector<int>& ans, set<pairii>& adjustments, int i) {
  fprintf(stderr, "\nsolve recursively:  a[0...%d]\n", i);
  auto [ x, max_i ] = *indices.rbegin();
  fprintf(stderr, "  max is %d at index %d\n", x, max_i);

  int min_beyond = INT_MAX;
  for (int j = max_i; j <= i; j++) {
    ans[j] = x;
    indices.erase({a[j], j});
    min_beyond = min(min_beyond, a[j]);
  }
  PRINTVEC(ans);

  // what does x get sent to?
  int x_sent_to = x;
  auto it = adjustments.lower_bound({x, -1});
  if (it != adjustments.begin()) {
    auto actual_it = prev(it);
    assert(x > actual_it->first);
    x_sent_to = max(x_sent_to, actual_it->second);
  }
  fprintf(stderr, "x sent to = %d\n", x_sent_to);
  auto it1 = adjustments.insert({min_beyond, x_sent_to}).first;
  for (auto it2 = next(it1); it2 != adjustments.end() && it2->second <= x_sent_to; ) {
    it2 = adjustments.erase(it2);
  }

  fprintf(stderr, "adjustments:\n");
  for (const auto& _p : adjustments)  fprintf(stderr, "  >%d  ->  %d\n", _p.first, _p.second);

  if (indices.empty())  return;
  solve_recursively(a, n, indices, ans, adjustments, max_i-1);

}


void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  set<pairii> indices;
  FORI(n)  indices.insert({a[i], i});
  // if you are > .first, then set ans to .second
  set<pairii> adjustments;

  vector<int> ans(n, -1);
  solve_recursively(a, n, indices, ans, adjustments, n-1);

  if (!adjustments.empty()) {
    for (int i = 0; i < n; i++) {
      int cur_ans = ans[i];
      auto it = adjustments.lower_bound({cur_ans, -1});
      if (it != adjustments.begin()) {
        auto actual_it = prev(it);
        assert(cur_ans > actual_it->first);
        cur_ans = max(cur_ans, actual_it->second);
        fprintf(stderr, "updating ans[%d] from %d to %d\n", i, ans[i], cur_ans);
        ans[i] = cur_ans;
      }
    }
  }

  for (int i = 0; i < n; i++)  cout << ans[i] << " ";
  cout << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
