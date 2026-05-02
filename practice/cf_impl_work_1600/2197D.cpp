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
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  long score = 0;

  for (int i = 0; i < n; i++) {
    long x = a[i];
    // scan forward
    for (int k = 1; k <= x; k++) {
      long j = i + x*k;
      if (j >= n)  break;
      if (a[j] == k) {
        score++;
      }
    }
    for (int k = 1; k < x; k++) {
      long j = i - x*k;
      if (j < 0)  break;
      if (a[j] == k) {
        score++;
      }
    }
  }

  cout << score << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
