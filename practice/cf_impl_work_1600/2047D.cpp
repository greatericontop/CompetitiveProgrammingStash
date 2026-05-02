#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld, ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif













void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  set<pair<int, int>> vals;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    vals.emplace(a[i], i);
  }
  int lowest_index = 0;

  vector<int> sorted_order;
  while (!vals.empty()) {
    auto [val, index] = *vals.begin();
    vals.erase(vals.begin());
    sorted_order.push_back(val);
    fprintf(stderr, "sorted_order += %d @ %d\n", val, index);

    for (int j = min(index-1, n-1); j >= lowest_index; j--) {
      auto it = vals.find({a[j], j});
      if (it == vals.end()) {
        it = vals.find({a[j], n+j});  //needs to maintain uniqueness, n+j works
        assert(it != vals.end());
      }
      vals.erase(it);
      a[j]++;
      vals.insert({a[j], n+j});
      fprintf(stderr, "  insert %d, %d(%d)\n", a[j], n+j, j);
    }
    lowest_index = index+1;

  }


  for (int i = 0; i < n; i++) {
    cout << sorted_order[i] << " ";
  }
  cout << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
