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

  int forced = n-k;
  for (int i = 0; i < forced; i++) {
    if (B[i] != -1 && A[i] != B[i]) {
      cout << "NO\n";
      return;
    }
  }
  for (int i = n-1; i >= n-forced; i--) {
    if (B[i] != -1 && A[i] != B[i]) {
      cout << "NO\n";
      return;
    }
  }

  multiset<int> A_center;
  multiset<int> B_center;
  for (int i = forced; i < n-forced; i++) {
    A_center.insert(A[i]);
    if (B[i] != -1)  B_center.insert(B[i]);
  }
  // B must be a subset of A
  for (int x : B_center) {
    auto it = A_center.find(x);
    if (it == A_center.end()) {
      cout << "NO\n";
      return;
    }
    A_center.erase(it);
  }
  // N log N

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