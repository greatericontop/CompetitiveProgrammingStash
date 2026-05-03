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

  vector<int> found_perm(n+1, -1);
  int cur_slot = 1;
  vector<int> results;
  results.pb(1);
  cout << "? 1" << endl;
  int _y; cin >> _y; assert(_y == 1);

  for (int q = 1; ; q++) {
    cout << "? " << cur_slot << endl;
    int x; cin >> x; assert(x != 0);
    if (results.empty()) {
      results.pb(x);
    } else {
      if (x == results.front()) {
        // cycle has been found
        int ptr = 0;
        while (results[ptr] != cur_slot)  ptr++;
        // ptr now points to occurrence of cur_slot
        int prev = cur_slot;
        for (int i = ptr+1; i <= ptr + (int)results.size(); i++) {
          int results_i = results[i % (int)results.size()];
          found_perm[prev] = results_i;
          prev = results_i;
        }
        PRINTVEC(found_perm);
        // advance to next empty slot
        results.clear();
        while (cur_slot <= n && found_perm[cur_slot] != -1)  cur_slot++;
        if (cur_slot > n) {
          break;
        }
      } else {
        results.pb(x);
      }
    }
  }

  cout << "! ";
  for (int i = 1; i <= n; i++) {
    cout << found_perm[i] << " ";
  }
  cout << endl;

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
