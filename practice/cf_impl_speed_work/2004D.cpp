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












using pcc = pair<char, char>;
void solve() {
  int n, q;
  cin >> n >> q;
  vector<pcc> a(n+1);
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    switch (s[0]) {
      case 'B': a[i].first = 0; break;
      case 'G': a[i].first = 1; break;
      case 'R': a[i].first = 2; break;
      case 'Y': a[i].first = 3; break;
    }
    switch (s[1]) {
      case 'B': a[i].second = 0; break;
      case 'G': a[i].second = 1; break;
      case 'R': a[i].second = 2; break;
      case 'Y': a[i].second = 3; break;
    }
  }

  vector<vector<int>> indices(16);
  for (int i = 1; i <= n; i++) {
    int idx = a[i].first*4 + a[i].second;
    indices[idx].push_back(i);
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    if (x > y)  swap(x, y);
    int x1 = a[x].first, x2 = a[x].second;
    int y1 = a[y].first, y2 = a[y].second;
    int xv = x1*4 + x2, yv = y1*4 + y2;
    if (x1 == y1 || x1 == y2 || x2 == y1 || x2 == y2) {
      // direct link
      cout << abs(y-x) << "\n";
      continue;
    }
    int best_cost = INT_MAX;
    for (int z = 0; z < 16; z++) {
      if (z == xv || z == yv) continue;  // not ==x or ==y
      if (indices[z].empty()) continue;
      // 200k * log(200k) * 6
      auto leftit = lower_bound(indices[z].rbegin(), indices[z].rend(), x, greater<int>());
      auto rightit = lower_bound(indices[z].begin(), indices[z].end(), x);
      int left_cost = INT_MAX, right_cost = INT_MAX;
      if (leftit != indices[z].rend()) {
        int left = *leftit;
        left_cost = abs(x - left) + abs(y - left);
      }
      if (rightit != indices[z].end()) {
        int right = *rightit;
        right_cost = abs(x - right) + abs(y - right);
      }
      int cost = min(left_cost, right_cost);
      best_cost = min(best_cost, cost);
    }
    if (best_cost == INT_MAX) {
      cout << "-1\n";
    } else {
      cout << best_cost << "\n";
    }
  }



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
