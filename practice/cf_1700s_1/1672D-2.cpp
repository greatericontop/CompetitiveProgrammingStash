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
using pairii = pair<int, int>;
using pairll = pair<long, long>;










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i)  cin >> a[i];
  vector<int> b(n);
  for (int i = 0; i < n; ++i)  cin >> b[i];

  multiset<int> movable_elts;
  int bptr = n-1;
  while (bptr >= 1 && b[bptr-1] == b[bptr]) {
    movable_elts.insert(b[bptr]);
    bptr--;
  }

  for (int aptr = n-1; aptr >= 0; aptr--) {
    // Try to match with bptr first
    if (bptr >= 0 && a[aptr] == b[bptr]) {
      fprintf(stderr, "take a=%d from bptr=%d\n", aptr, bptr);
      bptr--;
      while (bptr >= 1 && b[bptr-1] == b[bptr]) {
        movable_elts.insert(b[bptr]);
        bptr--;
      }
    } else {
      auto it = movable_elts.find(a[aptr]);
      if (it == movable_elts.end()) {
        cout << "NO\n";
        return;
      } else {
        movable_elts.erase(it);
      }
      fprintf(stderr, "take a=%d from extra set\n", aptr);
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
