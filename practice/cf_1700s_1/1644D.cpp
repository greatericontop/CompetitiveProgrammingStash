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
  int n, m, k, q;
  cin >> n >> m >> k >> q;
  vector<pairii> queries(q);
  for (int i = 0; i < q; i++) {
    cin >> queries[i].first >> queries[i].second;
  }

  int opcount = 0;
  set<int> blocked_rows;
  set<int> blocked_cols;

  for (int i = q-1; i >= 0; i--) {
    int r = queries[i].first;
    int c = queries[i].second;
    if ((blocked_rows.count(r) || blocked_cols.size() == m)
        && (blocked_cols.count(c) || blocked_rows.size() == n)
        ) {
      continue;
    }
    opcount++;
    blocked_rows.insert(r);
    blocked_cols.insert(c);
  }

  // calculate k^q, dumb linear way is fine
  long ans = 1;
  for (int i = 0; i < opcount; i++) {
    ans = (ans * k) % 998244353;
  }

  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
