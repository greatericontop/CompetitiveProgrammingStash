#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
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
  vector<long> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  int even_ct = 0, odd_ct = 0;
  for (int i = 0; i < m; i++) {
    int j;
    cin >> j;
    if (j % 2 == 0)  even_ct++;
    else  odd_ct++;
  }
  vector<long> even_a, odd_a;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 0)  even_a.push_back(a[i]);
    else  odd_a.push_back(a[i]);
  }
  sort(even_a.begin(), even_a.end());
  sort(odd_a.begin(), odd_a.end());

  long sum = 0;
  fprintf(stderr, "even_ct=%d odd_ct=%d\n", even_ct, odd_ct);
  PRINTVEC(even_a);
  PRINTVEC(odd_a);
  if (even_ct >= 1) {
    int j = (int)even_a.size() - 1;    // points to first elt deleted
    while (j > 0 && even_a[j-1] > 0)  j--;
    if (j < (int)even_a.size() - even_ct)  j = (int)even_a.size() - even_ct;
    fprintf(stderr, "cut evens at %d\n", j);
    for (int i = 0; i < j; i++)  sum += even_a[i];
  } else {
    for (long x : even_a)  sum += x;
  }
  if (odd_ct >= 1) {
    int j = (int)odd_a.size() - 1;
    while (j > 0 && odd_a[j-1] > 0)  j--;
    if (j < (int)odd_a.size() - odd_ct)  j = (int)odd_a.size() - odd_ct;
    fprintf(stderr, "cut odds at %d\n", j);
    for (int i = 0; i < j; i++)  sum += odd_a[i];
  } else {
    for (long x : odd_a)  sum += x;
  }

  cout << sum << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
