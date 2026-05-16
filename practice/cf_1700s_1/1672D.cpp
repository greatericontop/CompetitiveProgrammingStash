#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
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
#define long long long
#define pb push_back
using pairii = pair<int, int>;
using pairll = pair<long, long>;










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i)  cin >> a[i];
  vector<int> b(n);
  for (int i = 0; i < n; ++i)  cin >> b[i];

  vector<pairii> b_immovable;
  // b_movable[x] = set of all indices that contain x
  vector<set<int>> b_movable(n+1);
  for (int i = 0; i < n; i++) {
    if (i == 0 || b[i-1] != b[i]) {
      b_immovable.push_back({b[i], i});
    } else {
      b_movable[b[i]].insert(i);
    }
  }

  int b_ptr = 0;
  int last_immovable_i = -1;
  for (int a_ptr = 0; a_ptr < n; a_ptr++) {
    if (b_ptr < b_immovable.size() && a[a_ptr] == b_immovable[b_ptr].first) {
      // use an immovable element, or movable if its close
      if (!b_movable[a[a_ptr]].empty()) {
        int i = *b_movable[a[a_ptr]].begin();
        if (i < b_immovable[b_ptr].second) {
          b_movable[a[a_ptr]].erase(i);
          continue;
        }
      }
      last_immovable_i = b_immovable[b_ptr].second;
      b_ptr++;
    } else {
      // use earliest available movable element
      int x = a[a_ptr];
      if (b_movable[x].empty()) {
        cout << "NO\n";
        return;
      } else {
        int i = *b_movable[x].begin();
        if (i < last_immovable_i) {
          cout << "NO\n";
          return;
        } else {
          b_movable[x].erase(i);
        }
      }
    }
  }

  cout << "YES\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
