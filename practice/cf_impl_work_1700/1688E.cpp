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









#define cap first
#define index second

void solve() {
  int n, m;
  cin >> n >> m;
  vector<pairll> capacities(m);
  string s;
  for (int i = 0; i < m; i++)  s += '0';
  for (int i = 0; i < m; i++) {
    s[i] = '1';
    cout << "? " << s << endl;
    cin >> capacities[i].cap;
    capacities[i].index = i;
    s[i] = '0';
  }
  sort(capacities.begin(), capacities.end());

  // string s is currently all zeros
  s[capacities[0].index] = '1';
  long total = capacities[0].cap;
  for (int i = 1; i < m; i++) {
    fprintf(stderr, "i = %d\n", i);
    s[capacities[i].index] = '1';
    long expected_total_if_acyclic = total + capacities[i].cap;
    long actual_total;
    cout << "? " << s << endl;
    cin >> actual_total;
    if (actual_total == expected_total_if_acyclic) {
      total = actual_total;
    } else {
      // this edge can be discarded
      s[capacities[i].index] = '0';
    }
  }

  cout << "! " << total << endl;


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}
