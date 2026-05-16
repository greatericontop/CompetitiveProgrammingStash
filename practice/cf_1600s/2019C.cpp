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
  long n, k;
  cin >> n >> k;
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];
  long D = accumulate(a.begin(), a.end(), -1LL, [](long acc, long x) { return max(acc, x); });
  long s = accumulate(a.begin(), a.end(), 0LL);  //we can have s...s+k

  long best_decksize = -1;
  for (int decksize = 1; decksize <= n; decksize++) {
    long numdecks = (s + k) / decksize;
    long numcards = numdecks * decksize;
    assert(numcards <= s+k);
    assert(numcards > s+k-decksize);
    if (numcards >= s && numdecks >= D) {
      best_decksize = decksize;
    }
  }

  cout << best_decksize << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
