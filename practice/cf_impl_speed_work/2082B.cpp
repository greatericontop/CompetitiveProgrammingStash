#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d, ", _x); \
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
  int x;
  int floors, ceils;
  cin >> x >> floors >> ceils;
  if (floors >= 50)  floors = 50;  //enough to crash to zero
  if (ceils >= 50)  ceils = 50;  //enough to crash to 1

  //mini: ceils, then floors
  int mini = x;
  for (int i = 0; i < ceils; i++) {
    mini = (mini + 1) / 2;
  }
  for (int i = 0; i < floors; i++) {
    mini = mini / 2;
  }

  //maxi: floors, then ceils
  int maxi = x;
  for (int i = 0; i < floors; i++) {
    maxi = maxi / 2;
  }
  for (int i = 0; i < ceils; i++) {
    maxi = (maxi + 1) / 2;
  }

  cout << mini << " " << maxi << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
