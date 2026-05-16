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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










struct Segment {
  int l;
  int r;

  bool operator < (const Segment& other) const {
    if (l != other.l)  return l < other.l;
    return r < other.r;
  }
};

struct Event {
  int x;
  char type;  //'S' for start, 'E' for end
  Segment seg;
};


void solve() {
  int n, m;
  cin >> n >> m;
  vector<Segment> segments(n);
  for (int i = 0; i < n; i++) {
    cin >> segments[i].l >> segments[i].r;
  }
  map<int, vector<Event>> events;
  for (const auto& seg : segments) {
    events[seg.l].pb({seg.l, 'S', seg});
    events[seg.r+1].pb({seg.r+1, 'E', seg});
  }

  set<Segment> active;
  int touching_1_count = 0;
  int touching_m_count = 0;
  int best_score = INT_MIN;
  // check every x at/after an event
  for (const auto& [x, evs] : events) {
    for (const auto& event : evs) {
      if (event.type == 'S') {
        active.insert(event.seg);
        if (event.seg.l == 1)  touching_1_count++;
        if (event.seg.r == m)  touching_m_count++;
      } else {
        active.erase(event.seg);
        if (event.seg.l == 1)  touching_1_count--;
        if (event.seg.r == m)  touching_m_count--;
      }
    }
    fprintf(stderr, "x=%d,  active: %d, touching_1=%d, touching_m=%d\n", x, (int) active.size(), touching_1_count, touching_m_count);
    int score_here = active.size() - min(touching_1_count, touching_m_count);
    best_score = max(best_score, score_here);
  }

  cout << best_score << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
