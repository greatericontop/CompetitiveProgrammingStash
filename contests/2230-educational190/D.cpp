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









struct Event {
  int idx;
  bool type;  //true=ok, false=choke
};


struct Index {
  int idx;
  int count;
};


void solve() {
  int n;
  cin >> n;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  vector<int> b(n+1);
  for (int i = 1; i <= n; i++)  cin >> b[i];

  vector<vector<Event>> events(n+2);
  for (int i = 1; i <= n; i++) {
    if (a[i] == b[i]) {
      events[a[i]].pb({i, true});
    } else {
      events[a[i]].pb({i, false});
      events[b[i]].pb({i, false});
    }
  }
  for (int i = 1; i <= n+1; i++) {
    events[i].pb({n+1, false});
  }

  vector<Index> indices(n);
  vector<Index> new_indices;
  for (int i = 1; i <= n; i++)  indices[i-1] = {i, 1};

  long ans = 0;

  // Sweeping
  for (int cur = 1; cur <= n+1; cur++) {
    fprintf(stderr, "----- cur = %d\n", cur);
    fprintf(stderr, "indices:  \n");
    for (const auto& ind : indices)  fprintf(stderr, "[%d x%d]  ", ind.idx, ind.count);
    fprintf(stderr, "\n\n");


    vector<Event>& cur_events = events[cur];
    int i = 0;  //points to first unprocessed index
    for (int eptr = 0; eptr < cur_events.size(); eptr++) {
      Event& event = cur_events[eptr];
      int total_count_at_event = 0;
      while (i < indices.size() && indices[i].idx <= event.idx) {
        Index ind = indices[i];
        ans += LONG(ind.count) * LONG(event.idx - ind.idx);
        total_count_at_event += ind.count;
        i++;
      }
      if (event.type) {
        new_indices.pb({event.idx, total_count_at_event});
      }  //if event is a choke, indices do not carry on
    }
    assert(i == indices.size());  //should've gotten them all
    swap(indices, new_indices);
    new_indices.clear();


  }

  cout << ans << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
