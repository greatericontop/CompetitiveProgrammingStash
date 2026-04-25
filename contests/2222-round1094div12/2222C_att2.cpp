#include <bits/stdc++.h>
using namespace std;
//#define long long long


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


	#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;










void solve() {
  int n;
  cin >> n;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];

  set<int> values;
  for (int i = 1; i <= n; i++)  values.insert(a[i]);

  int best_ans = 0;

  for (int med : values) {
    int cur_ans = 0;
    int ct_l = 0, ct_r = 0, ct_m = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] < med)  ct_l++;
      else if (a[i] > med)  ct_r++;
      else  ct_m++;

      if ((ct_l + ct_r + ct_m) % 2 == 1 && (ct_m >= 1) && ((ct_l + ct_m > ct_r) || (ct_r + ct_m > ct_l))) {
        cur_ans++;
        ct_l = 0;
        ct_r = 0;
        ct_m = 0;
      }
    }
    if (ct_l != 0 || ct_r != 0 || ct_m != 0) {
      if (ct_l != ct_r) {
        // last one can be extended
        continue;
      }
    }
    best_ans = max(best_ans, cur_ans);
  }

  cout << best_ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
