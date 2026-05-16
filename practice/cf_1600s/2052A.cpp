#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


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
  vector<int> final_state(n);
  for (int i = 0; i < n; i++)  cin >> final_state[i];

  vector<int> cur(n);
  for (int i = 0; i < n; i++)  cur[i] = i + 1;
  vector<pair<int, int>> overtakes;

  for (int i = 0; i < n; i++) {
    int x = final_state[i];
    int indexof_x = lower_bound(cur.begin(), cur.end(), x) - cur.begin();
    assert(indexof_x < cur.size() && cur[indexof_x] == x);
    for (int j = indexof_x + 1; j < cur.size(); j++) {
      overtakes.emplace_back(cur[j], x);
    }
    for (int j = cur.size() - 1; j > indexof_x; j--) {
      overtakes.emplace_back(x, cur[j]);
    }
    cur.erase(cur.begin() + indexof_x);  //O(n)
    for (int j = indexof_x-1; j >= 0; j--) {
      overtakes.emplace_back(x, cur[j]);
    }
  }

  cout << overtakes.size() << "\n";
  for (const auto& p : overtakes) {
    cout << p.first << " " << p.second << "\n";
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
