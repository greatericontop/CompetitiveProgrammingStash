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
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];

  vector<int> prefix_gcd(n+1);
  prefix_gcd[1] = a[1];
  for (int i = 2; i <= n; i++) {
    prefix_gcd[i] = gcd(prefix_gcd[i-1], a[i]);
  }
  vector<int> suffix_gcd(n+1);
  suffix_gcd[n] = a[n];
  for (int i = n-1; i >= 1; i--) {
    suffix_gcd[i] = gcd(suffix_gcd[i+1], a[i]);
  }

  long total = 0;
  assert(suffix_gcd[1] == prefix_gcd[n]);
  total += prefix_gcd[n];  //edge connecting 1<->n

  for (int i = 2; i <= n-1; i++) {
    long cost1 = prefix_gcd[i];
    long cost2 = suffix_gcd[i];
    total += min(cost1, cost2);
  }

  cout << total << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
