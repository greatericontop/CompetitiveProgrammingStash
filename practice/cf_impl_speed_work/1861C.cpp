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
  string s;
  cin >> s;

  int n = 0;
  int sorted = -1;  //highest sorted index
  int unsorted = -1;  //lowest unsorted index
  for (char c : s) {
    if (c == '+') {
      n++;
    } else if (c == '-') {
      n--;
      if (unsorted != -1 && unsorted > n) {
        unsorted = -1;
      }
      if (sorted != -1 && sorted > n) {
        sorted = n;
      }
    } else if (c == '1') {
      if (unsorted != -1) {
        cout << "NO\n";
        return;
      }
      sorted = max(sorted, n);
    } else if (c == '0') {
      if (n == 0 || n == 1) {
        cout << "NO\n";
        return;
      }
      if (sorted != -1 && sorted >= n) {
        cout << "NO\n";
        return;
      }
      if (unsorted == -1) {
        unsorted = n;
      } else {
        unsorted = min(unsorted, n);
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
