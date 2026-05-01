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













void solve() {
  int n, m;
  cin >> n >> m;

  multiset<int> a;
  multiset<int> b;
  long suma = 0, sumb = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    a.insert(x);
    suma += x;
  }
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    b.insert(x);
    sumb += x;
  }

  if (suma != sumb) {
    cout << "NO\n";
    return;
  }

  // each step takes log time
  // at each step either both sizes decrease by 1, or size of b increases by 1, if b is ever larger than a, fail
  // so capped at around n+m steps
  while (!a.empty()) {
    if (b.size() > a.size()) {
      cout << "NO\n";
      return;
    }

    int amax = *a.rbegin();
    int bmax = *b.rbegin();
    if (amax == bmax) {
      a.erase(a.find(amax));
      b.erase(b.find(amax));
    } else if (amax > bmax) {
      // can't decrease amax
      cout << "NO\n";
      return;
    } else {
      // decrease bmax
      int b1 = bmax/2;
      int b2 = (bmax+1)/2;
      b.erase(b.find(bmax));
      b.insert(b1);
      b.insert(b2);
    }
  }

  assert(b.empty());
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
