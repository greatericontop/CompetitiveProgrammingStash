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
#define exp(x) (1 << (x))
template <class T, class Combiner> class SegmentTree {
private:
  int max_layer;
  int n;
  vector<vector<T>> segments; // segments[l] contains 0 to 2^l - 1
  Combiner combiner;
  T combine_empty; // the identity/null element (e.g. 0 for sum, INT_MAX for min, etc.)

public:
  explicit SegmentTree(int max_layer, Combiner combiner, T combine_empty, const vector<T>& initialize)
      : max_layer(max_layer), n(exp(max_layer)), segments(max_layer + 1),
        combiner(combiner), combine_empty(combine_empty) {
    assert(initialize.size() <= n);
    segments[0] = initialize;
    while (segments[0].size() < n)  segments[0].push_back(combine_empty);

    for (int layer = 1; layer <= max_layer; layer++) {
      for (int i = 0; i < exp(max_layer-layer); i++) {
        segments[layer].push_back(combiner(segments[layer-1][2*i], segments[layer-1][2*i+1]));
      }
    }
  }

  void point_update(int i, T new_value) {
    segments[0][i] = new_value;
    for (int layer = 1; layer <= max_layer; layer++) {
      i /= 2;
      segments[layer][i] = combiner(segments[layer-1][2*i], segments[layer-1][2*i+1]);
    }
  }

  /* Range query left to right inclusive, 0-indexed */
  T range_query(int left, int right) {
    T answer = combine_empty;
    while (left <= right) {
      // Find biggest interval (aka what's the biggest power of 2 that divides a)
      int layer_i = left;
      int layer = 0;
      while ((left % (2 << layer) == 0) && (layer < 18) && (left + (2 << layer) - 1 <= right)) {
        layer++;
        layer_i /= 2;
      }
      answer = combiner(answer, segments[layer][layer_i]);
      left += exp(layer);
    }
    return answer;
  }
};












void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<int> b(n);
  FORI(n)  cin >> b[i];

  vector<vector<int>> a_indices(n+1);
  FORI(n)  a_indices[a[i]].pb(i);

  vector<pairii> events(n);
  FORI(n)  events[i] = {b[i], i};
  sort(events.begin(), events.end());

  set<int> banned;
  banned.insert(-10); banned.insert(1e8);
  vector<int> banned_queued;
  int last_bi = -1;

  int logn = 1;
  while (exp(logn) < n+10)  logn++;
  auto max_combiner = [](const int a, const int b) { return max(a, b); };
  SegmentTree<int, decltype(max_combiner)> rmq(logn, max_combiner, INT_MIN, a);

  for (auto [bi, i] : events) {
    if (bi != last_bi) {
      for (int j : banned_queued)  banned.insert(j);
      banned_queued.clear();
      last_bi = bi;
    }
    fprintf(stderr, "Event: i=%d b[i]=%d\n", i, bi);
    fprintf(stderr, "  ");
    PRINTVEC(banned);
    auto itbanned = banned.lower_bound(i);
    assert(itbanned != banned.end() && itbanned != banned.begin());
    int banned_right = *itbanned;
    int banned_left = *prev(itbanned);

    bool success = false;
    vector<int>& indices = a_indices[bi];
    auto itright = lower_bound(indices.begin(), indices.end(), i);
    if (itright != indices.end()) {
      int right = *itright;
      assert(right >= i);  //equal is fine
      if (right <= banned_right && rmq.range_query(i, right) == bi) {
        success = true;
      }
    }
    if (itright != indices.begin()) {
      int left = *prev(itright);
      assert(left < i);
      if (left >= banned_left && rmq.range_query(left, i) == bi) {
        success = true;
      }
    }

    if (!success) {
      fprintf(stderr, "Failed on i=%d b[i]=%d\n", i, bi);
      cout << "NO\n";
      return;
    }

    banned_queued.pb(i);
  }

  cout << "YES\n";

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
