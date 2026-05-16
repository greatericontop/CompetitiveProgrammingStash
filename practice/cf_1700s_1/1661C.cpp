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
  vector<int> h(n);
  for (int i = 0; i < n; i++) cin >> h[i];
  sort(h.begin(), h.end());
  int hmax = h.back();

  long l = 0, r = 1e18;
  while (l < r) {
    long days = l + (r-l)/2;
    long plusones = (days+1)/2;
    long plustwos = days/2;
    for (int i = 0; i < n; i++) {
      long diff = hmax - h[i];
      long numtwos = min(diff/2, plustwos);
      diff -= numtwos*2;
      plustwos -= numtwos;
      plusones -= diff;
    }
    if (plusones >= 0 && plustwos >= 0) {
      // this works
      r = days;
    } else {
      l = days+1;
    }
  }
  long ans1 = l;


  hmax++;
  l = 0;
  r = 1e18;
  while (l < r) {
    long days = l + (r-l)/2;
    long plusones = (days+1)/2;
    long plustwos = days/2;
    for (int i = 0; i < n; i++) {
      long diff = hmax - h[i];
      long numtwos = min(diff/2, plustwos);
      diff -= numtwos*2;
      plustwos -= numtwos;
      plusones -= diff;
    }
    if (plusones >= 0 && plustwos >= 0) {
      // this works
      r = days;
    } else {
      l = days+1;
    }
  }
  long ans2 = l;


  cout << min(ans1, ans2) << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
