#include <bits/stdc++.h>
using namespace std;
#define long long long

//#define fprintf(...) // no-op





void solve() {
  int n, k;
  cin >> n >> k;

  vector<int> A(k+1); // start
  vector<int> B(k+1); // end

  for (int i = 1; i <= k; i++) {
    cout << "? " << i << endl;
    cin >> A[i];
  }
  int n_padded = n;
  while (n_padded % k != 0)  n_padded++;
  for (int i = 1; i <= k; i++) {
    int idx = n_padded - k + i;
    if (idx > n)  idx -= k;
    cout << "? " << idx << endl;
    cin >> B[i];
  }

  // diff[i] if predictions are different
  vector<bool> diff(k+1, false);
  for (int i = 1; i <= k; i++) {
    int pred_a = A[i];
    int pred_b = B[i];
    if (pred_a != pred_b)  diff[i] = true;
  }
  diff[0] = diff[k];

  // Failure condition
  int diff_i = -1;
  for (int i = 1; i <= k; i++) {
    if (diff[i]) {
      diff_i = i;
      break;
    }
  }
  if (diff_i == -1) {
    cout << "! -1" << endl;
    return;
  }

  // 0th group of :1...k:, etc.
  // Bin search for the last coordinate that A occurs
  int low = 0, high = n_padded / k - 1;
  while (low < high) {
    // TODO: off by 1
    int mid = (low + high + 1) / 2;
    cout << "? " << mid*k + diff_i << endl;
    int val;
    cin >> val;
    if (val == A[diff_i]) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }

  fprintf(stderr, "group = %d\n", low);
  int j = low*k + diff_i;
  fprintf(stderr, "j = %d\n", j);
  for (int o = 1; o <= k; o++) {
    int idx = j + o;
    // First one that switches to b
    cout << "? " << idx << endl;
    int val;
    cin >> val;
    if (diff[idx % k] && val == B[idx]) {
      if (diff[(idx-1) % k]) {
        cout << "! " << idx << endl;
        return;
      } else {
        cout << "! -1" << endl;
        return;
      }
    }
  }

  assert(false); // should have terminated by now
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}