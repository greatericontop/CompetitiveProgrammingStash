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
  int n;
  long c;
  cin >> n >> c;
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  multiset<long> vote_counts;
  for (int i = 0; i < n; i++) {
    vote_counts.insert(a[i]);
  }

  int no_change_winner = -1;
  int best_votes = -1;
  for (int i = 0; i < n; i++) {
    long votes = a[i] + (i == 0 ? c : 0);
    if (votes > best_votes) {  //higher i has to strictly beat lower i
      best_votes = votes;
      no_change_winner = i;
    }
  }


  for (int i = 0; i < n; i++) {
    if (i == no_change_winner) {
      cout << "0 ";
      continue;
    }
    // kill candidate i-1 (we've already killed everyone before)
    if (i >= 1) {
      auto it = vote_counts.find(a[i-1]);
      assert(it != vote_counts.end());
      vote_counts.erase(it);
      c += a[i-1];
    }
    long our_votes = a[i] + c;
    long win_votes = *vote_counts.rbegin();
    if (our_votes < win_votes) {  //if equal, we win
      cout << (i+1) << " ";  // 0...i-1 and 1 last one
    } else {
      cout << (i) << " ";
    }
  }
  cout << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
