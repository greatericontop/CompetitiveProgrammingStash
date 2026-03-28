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

  // Forcing
  for (int i = 0; i < n-k; i++) {
    if (A[i] != A[i+k]) {
      if (B[i] != -1 && B[i] != A[i]) {
        cout << "NO\n";
        return;
      }
      if (B[i+k] != -1 && B[i+k] != A[i+k]) {
        cout << "NO\n";
        return;
      }
      B[i] = A[i];
      B[i+k] = A[i+k];
    } else {
      // equal, then B[i] must = B[i+k]
      if (B[i] != -1 && B[i+k] != -1 && B[i] != B[i+k]) {
        cout << "NO\n";
        return;
      }
      if (B[i] != -1) {
        B[i+k] = B[i];
      }
      if (B[i+k] != -1) {
        int j = i;
        while (j >= 0 && B[j+k] != -1 && A[j] == A[j+k]) {
          B[j] = B[j+k];
          j -= k;
        }
      }
    }
  }

  // Check subset multisets
  // each[i] contains indices that store a number i
  vector<set<int>> each(n+1);
  for (int i = 0; i < k; i++) {
    each[A[i]].insert(i);
  }
  fprintf(stderr, "%d\n", each[5].size());
  for (int i = 0; i < k; i++) {
    if (B[i] != -1) {
      fprintf(stderr, "pre-check at %d, B[i] = %d\n", i, B[i]);
      if (each[B[i]].empty()) {
        fprintf(stderr, "pre-check fail at %d\n", i);
        cout << "NO\n";
        return;
      }
      int to_erase = * each[B[i]].begin();
      each[B[i]].erase(to_erase);
    }
  }

  for (int i = k+1; i < n; i++) {
    each[A[i]].insert(i);

    auto it = each[A[i-k]].find(i-k);
    if (it != each[A[i-k]].end()) {
      each[A[i-k]].erase(it);
    }

    if (B[i] != -1) {
      if (each[B[i]].empty()) {
        fprintf(stderr, "fail at %d\n", i);
        cout << "NO\n";
        return;
      }
      int to_erase = * each[B[i]].begin();
      each[B[i]].erase(to_erase);
    }
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