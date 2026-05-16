#include <bits/stdc++.h>
using namespace std;
#define long long long


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










void solve() {
  int n, m;
  cin >> n >> m;

  cout << "? 1 1" << endl;
  int k;
  cin >> k;

  if (k == 0) {
    cout << "! 1 1" << endl;
    return;
  } else if (k >= n) {
    int y = 1 + k;
    cout << "? 1 " << y << endl;
    int k2;
    cin >> k2;
    cout << "! " << (1+k2) << " " << y << endl;
    return;
  } else if (k >= m) {
    int x = 1 + k;
    cout << "? " << x << " 1" << endl;
    int k2;
    cin >> k2;
    cout << "! " << x << " " << (1+k2) << endl;
    return;
  } else {
    // L-shaped band
    int c = k+1;
    cout << "? " << c << " " << c << endl;
    int k2;
    cin >> k2;
    if (k2 == 0) {
      cout << "! " << c << " " << c << endl;
    } else {
      pair<int, int> p1 = {c, c-k2};
      pair<int, int> p2 = {c-k2, c};
      cout << "? " << p1.first << " " << p1.second << endl;
      int k3;
      cin >> k3;
      if (k3 == 0) {
        cout << "! " << p1.first << " " << p1.second << endl;
      } else {
        assert(k3 == k2);
        cout << "! " << p2.first << " " << p2.second << endl;
      }
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
