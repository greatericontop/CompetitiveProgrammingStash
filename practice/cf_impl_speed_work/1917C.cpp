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










/* Return score from the state of :a: after :ops: ops, with :d: total ops allowed */
long check(const vector<long>& a, int ops, int d) {
  if (ops == d) {  //can't clear anymore
    return 0;
  }
  long score = 0;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == i+1)  score++;
  }
  ops++;  //pay 1 op to clear
  score += (d-ops)/2;
  return score;
}


void solve() {
  int n, k, d;
  cin >> n >> k >> d;
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];
  vector<int> v(k);
  for (int i = 0; i < k; i++)  cin >> v[i];

  long best = INT_MIN;
  for (int ops = 0; (ops < 2*n+5 && ops <= d); ops++) {
    long score = check(a, ops, d);
    best = max(best, score);
    // perform op
    int i = v[ops%k];
    for (int j = 0; j < i; j++) {
      a[j]++;
    }
  }

  cout << best << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
