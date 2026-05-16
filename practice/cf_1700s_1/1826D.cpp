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










void solve() {
  int n;
  cin >> n;
  vector<int> b(n);
  priority_queue<pairii> indices;
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    indices.push({b[i], i});
  }

  set<pairii> arr;
  FORI(2) {
    auto [val, idx] = indices.top();
    indices.pop();
    arr.insert({idx, val});
  }

  int best = (int)-1e9;
  for (int i = 2; i < n; i++) {
    auto [val, idx] = indices.top();
    indices.pop();
    arr.insert({idx, val});
    auto it = arr.find({idx, val});
    auto nextit = next(it);

    if (nextit != arr.end() && next(nextit) != arr.end()) {
      int indexsize = next(nextit)->first - it->first;
      int score = val + nextit->second + next(nextit)->second - indexsize;
      fprintf(stderr, "[%d %d] %d %d %d  ->  %d\n", it->first, next(nextit)->first, val, nextit->second, next(nextit)->second, score);
      best = max(best, score);
    }
    if (it != arr.begin()) {
      auto previt = prev(it);
      if (previt != arr.begin()) {
        int indexsize = it->first - prev(previt)->first;
        int score = val + previt->second + prev(previt)->second - indexsize;
        fprintf(stderr, "[%d %d] %d %d %d  ->  %d\n", prev(previt)->first, it->first, prev(previt)->second, previt->second, val, score);
        best = max(best, score);
      }
      if (nextit != arr.end()) {
        int indexsize = nextit->first - previt->first;
        int score = val + previt->second + nextit->second - indexsize;
        fprintf(stderr, "[%d %d] %d %d %d  ->  %d\n", previt->first, nextit->first, previt->second, val, nextit->second, score);
        best = max(best, score);
      }
    }
  }
  assert(indices.empty());

  cout << best << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
