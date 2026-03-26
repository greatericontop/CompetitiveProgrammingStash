#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op




/*
 * Evaluate objective function with argument :count:
 * O(n)
 */
long f(int n, long k, const vector<long>& A, long count) {
  if (count == 0)  return 0;
  vector<long> new_A(n);
  // :count: from the front/longest
  long count_left = count;
  int i = 0;
  for (; i < n-1; i++) {
    // A[0...i] are currently all A[i]
    if ((i+1) * (A[i] - A[i+1]) >= count_left) {
      // end condition
      long full = count_left / (i+1);
      long rem = count_left % (i+1);
      for (int z = 0; z <= i; z++) {
        new_A[z] = A[i] - full - (z < rem ? 1 : 0);
      }
      break; // i stores the last index that is touched
    }
    count_left -= (i+1) * (A[i] - A[i+1]);
    if (i == (n-2))  return 5'000'000'000'000'000'000LL + count; // we should have terminated by now
  }

  count_left = count;
  int j = n-1;
  for (; j >= 1; j--) {
    if ((n-j) * (A[j-1] - A[j]) >= count_left) {
      long full = count_left / (n-j);
      long rem = count_left % (n-j);
      for (int z = n-1; z >= j; z--) {
        new_A[z] = A[j] + full + (z >= n-rem ? 1 : 0);
      }
      break; // j stores the last index that is touched
    }
    count_left -= (n-j) * (A[j-1] - A[j]);
    if (j == 1)  return 5'000'000'000'000'000'000LL + count; // we should have terminated by now
  }

  if (i >= j) {
    //fprintf(stderr, "i, j touch! illegal!\n");
    return 5'000'000'000'000'000'000LL + count;
  }

  // lower is better
  long offset = 0;
  for (int z = 0; z <= i; z++) {
    // save A[z] ... new_A[z]
    long sum = (A[z] + new_A[z] + 1) * (A[z] - new_A[z]) / 2;
    offset -= sum;
  }
  for (int z = j; z < n; z++) {
    // lose A[z] ... new_A[z]
    long sum = (A[z] + new_A[z] + 1) * (new_A[z] - A[z]) / 2;
    offset += sum;
  }
  offset += k * count;
  return offset;
}


void solve() {
  int n;
  long k;
  cin >> n >> k;
  vector<long> A(n);
  for (int i = 0; i < n; i++)  cin >> A[i];
  sort(A.begin(), A.end(), greater<long>());

  long cur_ans = 0;
  long total_cars = 0;
  for (int i = 0; i < n; i++) {
    cur_ans += A[i] * (A[i] + 1) / 2;
    total_cars += A[i];
  }


  /*
   * Basic ternary search template for future use
   */
  long low = 0, high = total_cars;
  while (low + 5 <= high) { // somewhat arbitrary, just have it to avoid base case issues, and I *think* 5 is the best choice
    long mid1 = low + (high-low)/2;
    long mid2 = mid1 + 1;
    long f1 = f(n, k, A, mid1);
    long f2 = f(n, k, A, mid2);
    if (f1 < f2) {
      high = mid2-1;
    } else if (f1 > f2) {
      low = mid1+1;
    } else {
      low = mid1;
      high = mid2;
    }
  }
  long best = f(n, k, A, low);
  for (long i = low+1; i <= high; i++) {
    long cur = f(n, k, A, i);
    if (cur < best) {
      best = cur;
      low = i;
    }
  }
  /* Answer in :best: and :low: */


  long ans = cur_ans + best;
  if (ans >= 5'000'000'000'000'000'000LL) {
    ans = cur_ans;
  }
  cout << ans << "\n";
}





int main() {
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}