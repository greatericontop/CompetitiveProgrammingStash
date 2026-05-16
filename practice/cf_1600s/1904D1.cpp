#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


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










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];
  vector<int> b(n);
  for (int i = 0; i < n; i++)  cin >> b[i];

  vector<pair<int, int>> indices;
  for (int i = 0; i < n; i++)  indices.emplace_back(b[i], i);
  sort(indices.begin(), indices.end());

  for (auto& [goal, i] : indices) {
    if (goal < a[i]) {
      cout << "NO\n";
      return;
    }
    if (goal == a[i])  continue;
    // sweep left and right, goal is to find a[j]==goal, cannot sweep a b[j] less than goal or a[j] greater than goal
    int left = i-1;
    bool found_goal = false;
    while (left >= 0) {
      if (a[left] == goal) {
        found_goal = true;
        break;
      }
      if (a[left] > goal || b[left] < goal) {
        left = i; // don't need to touch this part of the array
        break;
      }
      left--;
    }
    if (!found_goal)  left = i;
    int right = i+1;
    if (found_goal) {
      right = i;
    } else {
      while (right < n) {
        if (a[right] == goal) {
          found_goal = true;
          break;
        }
        if (a[right] > goal || b[right] < goal) {
          right = i;
          break;
        }
        right++;
      }
    }
    if (!found_goal) {
      cout << "NO\n";
      return;
    } else {
      for (int j = left; j <= right; j++) {
        a[j] = goal;
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
