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









struct Event {
  int i;
  int min;
  int max;

  bool operator < (const Event& other) const {
    if (max != other.max)  return max < other.max;
    return i < other.i;
  }
};


void solve() {
  int n;
  cin >> n;
  vector<Event> events(n);
  for (int i = 1; i <= n; i++) {
    int bi;
    cin >> bi;
    events[i-1].i = i;

    // bin search for min that satisfies bi = floor(i / ai)
    int l = 1, r = n;
    while (l < r) {
      int mid = l + (r-l)/2;
      if (bi < i/mid) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    events[i-1].min = l;

    // bin search for max that satisfies bi = floor(i / ai)
    l = 1; r = n;
    while (l < r) {
      int mid = l + (r-l+1)/2;
      if (bi > i/mid) {
        r = mid - 1;
      } else {
        l = mid;
      }
    }
    events[i-1].max = l;
  }


  for (const auto& e : events) {
    fprintf(stderr, "i=%d, min=%d, max=%d\n", e.i, e.min, e.max);
  }


  sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
    return a.min < b.min;
  });

  vector<int> ans(n+1, -1);
  int eptr = 0;
  set<Event> active_intervals;  //sorted by max
  // Assign x greedily, to the lowest max interval
  for (int x = 1; x <= n; x++) {
    while (eptr < n && events[eptr].min == x) {
      active_intervals.insert(events[eptr]);
      eptr++;
    }
    assert(!active_intervals.empty());
    auto it = active_intervals.begin();
    ans[it->i] = x;
    active_intervals.erase(it);

    // sanity check
    if (!active_intervals.empty()) {
      // no interval should have been cut off
      assert(x < active_intervals.begin()->max);
    }
  }


  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
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

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */
