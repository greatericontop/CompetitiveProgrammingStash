#include <bits/stdc++.h>
using namespace std;


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
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
using pairii = pair<int, int>;
using pairll = pair<long, long>;










void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  int bestscore = INT_MAX;
  int maxa = *max_element(a.begin(), a.end());
  for (int M = 0; M <= maxa; M++) {
    int mini = INT_MAX;
    bool possible = true;
    for (int i = 0; i < n; i++) {
      int pi;
      if (M == 0) {
        pi = a[i]+1;
      } else {
        // ai / pi < M+1
        pi = (a[i]+M+1) / (M+1);
      }
      if (pi > k)  pi = k;
      mini = min(mini, a[i]/pi);
      if (a[i]/pi > M) {
        possible = false;
        break;
      }
    }
    if (!possible) {
      continue;
    }
    fprintf(stderr, "max %d min %d\n", M, mini);
    int score = M - mini;
    bestscore = min(bestscore, score);
  }

  cout << bestscore << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}
