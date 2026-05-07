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
using AdjList = vector<vector<int>>;










int fill(int v, const AdjList& adj, const vector<int>& left, const vector<int>& right, vector<long>& fills) {
  int ops = 0;
  long total_fill = 0;
  for (int u : adj[v]) {
    ops += fill(u, adj, left, right, fills);
    total_fill += fills[u];
  }
  if (total_fill < left[v]) {
    fills[v] = right[v];
    ops++;
  } else {
    fills[v] = min(total_fill, (long) right[v]);
  }
  fprintf(stderr, "v=%d, %d ops to get fill %lld\n", v, ops, fills[v]);
  return ops;
}


void solve() {
  int n;
  cin >> n;
  AdjList adj(n);
  for (int i = 1; i < n; i++) {
    int pi;
    cin >> pi;
    pi--;
    adj[pi].pb(i);
  }
  vector<int> left(n), right(n);
  for (int i = 0; i < n; i++) {
    cin >> left[i] >> right[i];
  }

  vector<long> fills(n);
  int ops = fill(0, adj, left, right, fills);

  cout << ops << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
