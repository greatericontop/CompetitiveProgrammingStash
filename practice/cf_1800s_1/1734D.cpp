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










struct Entry {
  long delta;
  long lowest_pt;
  int idx;
};
void solve() {
  int n, k;
  cin >> n >> k;
  vector<long> a(n+1);
  FORI1(n)  cin >> a[i];
  vector<long> a_prefix_sum(n+1, 0);
  for (int i = 1; i <= n; i++)  a_prefix_sum[i] = a_prefix_sum[i-1] + a[i];

  vector<Entry> data(n+1);
  data[k] = {0, 0, k};  //0 delta, 0 lowest point (written as a delta on the left side)
  for (int i = k-1; i >= 0; i--) {
    long total_delta = data[i+1].delta + a[i];
    long lowest_point = min(data[i+1].lowest_pt, total_delta);
    data[i] = {total_delta, lowest_point, i};
  }
  for (int i = k+1; i <= n; i++) {
    long total_delta = data[i-1].delta + a[i];
    long lowest_point = min(data[i-1].lowest_pt, total_delta);
    data[i] = {total_delta, lowest_point, i};
  }


  // these are my own comments fyi not chatgpt lmao
  // Sorted by highest total_delta first
  auto cmp1 = [](const Entry& p1, const Entry& p2) {
    if (p1.delta != p2.delta)  return p1.delta > p2.delta;
  };
  multiset<Entry, decltype(cmp1)> active_set_left(cmp1);
  multiset<Entry, decltype(cmp1)> active_set_right(cmp1);
  // Sorted by highest lowest_point first
  auto cmp2 = [](const Entry& p1, const Entry& p2) {
    return p1.lowest_pt > p2.lowest_pt;
  };
  multiset<Entry, decltype(cmp2)> inactive_set_left(cmp2);
  multiset<Entry, decltype(cmp2)> inactive_set_right(cmp2);
  for (int i = 0; i < k; i++)  inactive_set_left.insert(data[i]);
  for (int i = k+1; i <= n; i++)  inactive_set_right.insert(data[i]);
  // Farthest touched left/right indices
  int l = k, r = k;
  long initial_hp = a[k], claimed_left_delta = 0, claimed_right_delta = 0;

  while (true) {
    fprintf(stderr, "l: %d, r: %d, claimed_left_delta: %lld, claimed_right_delta: %lld, total health %lld\n", l, r, claimed_left_delta, claimed_right_delta, initial_hp + claimed_left_delta + claimed_right_delta);
    // Refresh inactive sets if our health went up
    long minimum_allowed_left_delta = -(initial_hp + claimed_right_delta);
    while (!inactive_set_left.empty() && inactive_set_left.begin()->lowest_pt >= minimum_allowed_left_delta) {
      active_set_left.insert(*inactive_set_left.begin());
      inactive_set_left.erase(inactive_set_left.begin());
    }
    long minimum_allowed_right_delta = -(initial_hp + claimed_left_delta);
    while (!inactive_set_right.empty() && inactive_set_right.begin()->lowest_pt >= minimum_allowed_right_delta) {
      active_set_right.insert(*inactive_set_right.begin());
      inactive_set_right.erase(inactive_set_right.begin());
    }
    // Prune invalid entries in left and right active set
    while (!active_set_left.empty() && active_set_left.begin()->idx >= l)  active_set_left.erase(active_set_left.begin());
    while (!active_set_right.empty() && active_set_right.begin()->idx <= r)  active_set_right.erase(active_set_right.begin());

    bool made_progress = false;
    // See if we can search left
    if (!active_set_left.empty()) {
      auto entry = *active_set_left.begin();
      if (entry.delta > claimed_left_delta) {
        made_progress = true;
        claimed_left_delta = entry.delta;
        int l_old = l;
        l = entry.idx;
        assert(l < l_old);
        fprintf(stderr, "claiming left, new l is %d\n", l);
        //lazy delete above
      }
    }
    // See if we can search right
    if (!active_set_right.empty()) {
      auto entry = *active_set_right.begin();
      if (entry.delta > claimed_right_delta) {
        made_progress = true;
        claimed_right_delta = entry.delta;
        int r_old = r;
        r = entry.idx;
        assert(r > r_old);
        fprintf(stderr, "claiming right, new r is %d\n", r);
      }
    }

    if (!made_progress)  break;
  }


  long total_hp = initial_hp + claimed_left_delta + claimed_right_delta;
  bool left_works = true;
  long h = total_hp;
  for (int i = l-1; i >= 0; i--) {
    h += a[i];
    if (h < 0) {
      left_works = false;
      break;
    }
  }
  bool right_works = true;
  h = total_hp;
  for (int i = r+1; i <= n; i++) {
    h += a[i];
    if (h < 0) {
      right_works = false;
      break;
    }
  }

  fprintf(stderr, "loop finished l=%d r=%d, total_hp: %lld, left_works: %d, right_works: %d\n", l, r, total_hp, left_works, right_works);

  if (left_works || right_works) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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
