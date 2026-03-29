#include <bits/stdc++.h>
using namespace std;
#define long long long

//#define fprintf(...) // no-op





long lcm(int a, int b) {
  return ((long)a) * ((long)b) / ((long)gcd(a, b));
}

void solve() {
  int n;
  cin >> n;
  vector<int> A(n);
  vector<int> B(n);
  for (int i = 0; i < n; i++)  cin >> A[i];
  for (int i = 0; i < n; i++)  cin >> B[i];

  vector<int> requires_adjust;
  vector<int> max_multiplier(n);
  int count = 0;

  for (int i = 0; i < n; i++) {
    long x;
    if (i == 0) {
      x = gcd(A[0], A[1]);
    } else if (i == n-1) {
      x = gcd(A[n-1], A[n-2]);
    } else {
      x = lcm(gcd(A[i], A[i-1]), gcd(A[i], A[i+1]));
    }
    if (B[i] < x) {
      // can't adjust
      continue;
    }
    if (x == A[i]) {
      if (B[i] < 2*x) {
        continue;
      }
      requires_adjust.push_back(i);
      max_multiplier[i] = B[i] / x;
      count++;
    } else {
      count++;
    }
  }

  // Sweep
  int loss = 0;
  if (requires_adjust.size() > 0) {

    vector<int> problematic_indices;
    vector<bool> found_5;
    int i = requires_adjust[0];
    for (int j = 0; j < requires_adjust.size(); j++) {
      if (requires_adjust[j] != i) {
        // This segment is over
        bool paid_for_last_segment = false;
        for (int k = 0; k < ((int)problematic_indices.size()-1); k++) { // k, k+1
          if (found_5[k]) {
            paid_for_last_segment = false;
            continue;
          }
          if ((problematic_indices[k+1] - problematic_indices[k]) % 2 == 1) {
            if (paid_for_last_segment) {
              paid_for_last_segment = false;
            } else {
              loss++;
              paid_for_last_segment = true;
            }
          }
        }

        problematic_indices.clear();
        found_5.clear();
        i = requires_adjust[j];
      }
      // Extend this segment
      if (max_multiplier[requires_adjust[j]] == 2) {
        problematic_indices.push_back(requires_adjust[j]);
        found_5.push_back(false);
      }
      if (max_multiplier[requires_adjust[j]] >= 5 && found_5.size() > 0) {
        found_5.back() = true;
      }
      i++;
    }
    bool paid_for_last_segment = false;
    for (int k = 0; k < ((int)problematic_indices.size()-1); k++) { // k, k+1
      if (found_5[k]) {
        paid_for_last_segment = false;
        continue;
      }
      if ((problematic_indices[k+1] - problematic_indices[k]) % 2 == 1) {
        if (paid_for_last_segment) {
          paid_for_last_segment = false;
        } else {
          loss++;
          paid_for_last_segment = true;
        }
      }
    }

  }

  cout << count - loss << "\n";
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}