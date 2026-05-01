#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


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
  int n, m;
  cin >> n >> m;
  vector<int> people;
  vector<int> problems;
  int our_rating;
  for (int i = 0; i < n; i++) {
    int p;
    cin >> p;
    if (i == 0) {
      our_rating = p;
    } else {
      if (p > our_rating)  people.push_back(p);
    }
  }
  for (int i = 0; i < m; i++) {
    int d;
    cin >> d;
    if (d > our_rating)  problems.push_back(d);
  }
  sort(people.begin(), people.end());
  sort(problems.begin(), problems.end());
  PRINTVEC(people);
  PRINTVEC(problems);


  for (int k = 1; k <= m; k++) {
    fprintf(stderr, "k=%d\n", k);
    // k problems per contest
    int contests = m/k;
    int leftover_problems = m%k;


    long total_rank = 0;  //+1+how many beat us, per contest
    for (int c = 0; c < contests; c++) {
      int diff;
      int p_index = leftover_problems + c*k;
      if (p_index >= problems.size()) {
        diff = INT_MAX;  //we solve all problems, so we beat everyone
        fprintf(stderr, "  AK\n");
      } else {
        diff = problems[p_index];
        fprintf(stderr, "  diff=%d\n", diff);
      }
      // find first index j in people that is >= diff
      auto it = lower_bound(people.begin(), people.end(), diff);
//      int j;
//      if (it == people.end()) {
//        j = people.size();
//      } else {
//        j = it - people.begin();
//      }
      int j = it - people.begin();
      fprintf(stderr, "      rank %zu\n", 1 + (people.size() - j));
      total_rank += 1 + (people.size() - j);
    }

    cout << total_rank << " \n"[k==m];
  }



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
