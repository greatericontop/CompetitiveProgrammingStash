#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> A(n);
  for (int i = 0; i < n; i++)  cin >> A[i];
  vector<int> B(n);
  for (int i = 0; i < n; i++)  cin >> B[i];
  // Forced moves
  vector<int> C(n, -1);

  multiset<int> interesting_subgroups;
  multiset<int> interesting_subgroup_forced_nums;

  for (int g = 0; g < k; g++) {
    // Subgroup g mod k
    bool all_a_equal = true;
    for (int i = g; i < n; i += k) {
      if (A[i] != A[g]) {
        all_a_equal = false;
        break;
      }
    }
    if (!all_a_equal) {
      // Each B[i] is forced equal to A[i]
      for (int i = g; i < n; i += k) {
        if (B[i] != -1 && B[i] != A[i]) {
          cout << "NO\n";
          return;
        }
      }
    } else {
      interesting_subgroups.insert(A[g]);
      // Find if we are forced
      bool exists_b = false;
      int b_force;
      for (int i = g; i < n; i += k) {
        if (B[i] != -1) {
          exists_b = true;
          b_force = B[i];
          break;
        }
      }
      if (exists_b) {
        interesting_subgroup_forced_nums.insert(b_force);
        for (int i = g; i < n; i += k) {
          if (B[i] != -1 && B[i] != b_force) {
            cout << "NO\n";
            return;
          }
        }
      }
    }
  }

  // Is it a subset
  for (int x : interesting_subgroup_forced_nums) {
    auto it = interesting_subgroups.find(x);
    if (it == interesting_subgroups.end()) {
      cout << "NO\n";
      return;
    }
    interesting_subgroups.erase(it);
  }

  cout << "YES\n";

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}