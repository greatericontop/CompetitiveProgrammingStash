#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





/* Return (l, r) if there exists a submedian of >= v, or (-1, -1) if not possible. */
pair<int, int> works(int n, const vector<int>& A, int k, int v) {
  fprintf(stderr, "test v = %d\n", v);
  vector<int> B(n+1);
  for (int i = 1; i <= n; i++) {
    B[i] = (A[i] >= v) ? 1 : -1;
  }

  // Max subarray sum, but with odd penalty, and must have size at least k.
  vector<long> prefix_sum(n+1);
  prefix_sum[0] = 0;
  long best_even_prefix_sum = INT_MAX * 100000LL;
  int best_even_i = -1;
  long best_odd_prefix_sum = INT_MAX * 100000LL;
  int best_odd_i = -1;

  for (int i = 1; i <= n; i++) {
    prefix_sum[i] = prefix_sum[i-1] + B[i];

    if (i >= k) {
      int j = i - k; // 1 before the start of the subarray
      // Update best prefix sums
      if (j % 2 == 0) {
        if (prefix_sum[j] < best_even_prefix_sum) {
          best_even_prefix_sum = prefix_sum[j];
          best_even_i = j;
        }
      } else {
        if (prefix_sum[j] < best_odd_prefix_sum) {
          best_odd_prefix_sum = prefix_sum[j];
          best_odd_i = j;
        }
      }

      // Who do we use?
      long best_sum;
      int best_i;
      if (i % 2 == 0) {
        best_sum = best_even_prefix_sum;
        best_i = best_even_i;
        if (best_odd_prefix_sum + 1 < best_sum) {
          best_sum = best_odd_prefix_sum + 1;
          best_i = best_odd_i;
        }
      } else {
        best_sum = best_odd_prefix_sum;
        best_i = best_odd_i;
        if (best_even_prefix_sum + 1 < best_sum) {
          best_sum = best_even_prefix_sum + 1;
          best_i = best_even_i;
        }
      }

      fprintf(stderr, "  i = %d, best sum = %lld from i=%d\n", i, best_sum, best_i);

      if (prefix_sum[i] - best_sum >= 0) {
        fprintf(stderr, "  found %d, %d\n", best_i + 1, i);
        return {best_i + 1, i};
      }
    }
  }

  fprintf(stderr, "  return impossible\n");
  return {-1, -1};
}

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> A(n+1);
  for (int i = 1; i <= n; i++)  cin >> A[i];

  int low = 0;
  int high = n;
  while (low < high) {
    int mid = (low + high + 1) / 2;
    if (works(n, A, k, mid).first != -1) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }
  pair<int, int> ans = works(n, A, k, low);
  cout << low << " " << ans.first << " " << ans.second << "\n";
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}