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
  int n, x;
  cin >> n >> x;
  map<int, int> freq;
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;
    freq[v]++;
  }

  for (int i = 1; i < x; i++) {
    // i to i+1
    int ct = freq[i];
    if (ct % (i+1) != 0) {
      cout << "No\n";
      return;
    } else {
      freq[i+1] += ct / (i+1);
    }
  }

  cout << "Yes\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
