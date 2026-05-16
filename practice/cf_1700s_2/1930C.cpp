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










struct Interval {
  int left;
  int right;
};

struct Event {
  int pos;
  Interval interv;
  char type;  // 'E' end on left, 'S' start on right
};

void solve() {
  int n;
  cin >> n;
  vector<int> a(n+1);
  vector<Event> events;
  int xstart = INT_MIN;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    Interval interval = {a[i]+1, a[i]+i};
    xstart = max(xstart, interval.right);
    events.push_back({interval.left-1, interval, 'E'});
    events.push_back({interval.right, interval, 'S'});
  }
  sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
    return e1.pos > e2.pos;  //highest position first
  });


  auto interval_cmp = [](const Interval& i1, const Interval& i2) {
    if (i1.left != i2.left)  return i1.left > i2.left;
    return i1.right > i2.right;
  };
  set<Interval, decltype(interval_cmp)> active_intervals(interval_cmp);  //sorted by highest left endpoint first
  int event_ptr = 0;
  vector<int> ans;

  for (int x = xstart; x >= 0; ) {
    while (event_ptr < events.size() && events[event_ptr].pos == x) {
      if (events[event_ptr].type == 'S') {
        active_intervals.insert(events[event_ptr].interv);
      } else {
        active_intervals.erase(events[event_ptr].interv);
      }
      event_ptr++;
    }

    if (!active_intervals.empty()) {
      ans.pb(x);
      auto it = active_intervals.begin();  //greedily remove most-about-to-die interval
      active_intervals.erase(it);
      x--;
    } else {
      // move to next interesting x
      if (event_ptr < events.size()) {
        x = events[event_ptr].pos;
      } else {
        break;
      }
    }
  }


  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << " \n"[i == ans.size() - 1];
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
