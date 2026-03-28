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
    }
    int j = i;
    while (j >= k && A[j] == A[j-k] && B[j] != -1 && B[j-k] == -1) {
      B[j-k] = B[j];
      j -= k;
    }
  }

  fprintf(stderr, "After forcing:\n");
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "%d ", B[i]);
  }
  fprintf(stderr, "\n");


//  multiset<int> A_s;
//  multiset<int> B_s;
//  for (int i = 0; i < k; i++) {
//    A_s.insert(A[i]);
//    if (B[i] != -1) {
//      B_s.insert(B[i]);
//    }
//  }
//  // B subset A
//  for (int x : B_s) {
//    auto it = A_s.find(x);
//    if (it == A_s.end()) {
//      cout << "NO\n";
//      return;
//    }
//    A_s.erase(it);
//  }

  // Check subset multisets
  // each[i] contains indices that store a number i
  vector<set<int>> each(n+1);
  for (int i = 0; i < k; i++) {
    each[A[i]].insert(i);
  }
  for (int i = 0; i < k; i++) {
    if (B[i] != -1) {
      if (each[B[i]].empty()) {
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