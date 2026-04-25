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
  fprintf(stderr, "input read\n");
  map<int, int> first_occurrence;
  vector<int> to_i(n+1);
  int y = 0;
  for (int i = 1; i <= n; i++) {
    if (first_occurrence[a[i]] == 0)  first_occurrence[a[i]] = ++y;
    to_i[i] = first_occurrence[a[i]];
  }
  //PRINTMAP(first_occurrence);
//  vector<int> to_dp_index(n+1);
//  for (int i = 1; i <= n; i++) {
//    to_dp_index[i] = first_occurrence[a[i]];
//  }
  PRINTVEC(to_i);

  vector<vector<int>> dp(n+1, vector<int>(y+3, -1));
  dp[0] = vector<int>(y+3, 0); // 0-length subarrays for each median, base case

  for (int i = 1; i <= n; i++) {
    Tree<pair<int, int>> nums;
    nums.insert({a[i], i});
    for (int j = i; j >= 1; j -= 2) {
      auto & cur_median_pair = (* nums.find_by_order(nums.size()/2));
      int cur_median = cur_median_pair.first;
      int cur_median_dp_index = to_i[cur_median_pair.second];
      //assert(cur_median_dp_index <= n);
      if (dp[j-1][cur_median_dp_index] != -1) {
        dp[i][cur_median_dp_index] = max(dp[i][cur_median_dp_index], dp[j - 1][cur_median_dp_index] + 1);
      }
      // transition to next
      if (j - 2 >= 1) {
        nums.insert({a[j-1], j-1});
        nums.insert({a[j-2], j-2});
      }
    }
  }

  int ans = -1;
  for (int x : dp[n]) {
    //assert(x == -1 || (x % 2 == 1));
    ans = max(ans, x);
  }
  //assert(ans >= 1);
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
