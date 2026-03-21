#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  vector<int> A(n);
  for (int i = 0; i < n; i++)  cin >> A[i];

  vector<int> answers(n);
  multiset<int> processed;

  answers[n-1] = 0;
  processed.insert(A[n-1]);

  for (int i = n - 2; i >= 0; i--) {
    // Can use OST for faster runtime
    int less_than_us = 0;
    int more_than_us = 0;
    for (int x : processed) {
      if (x < A[i]) {
        less_than_us++;
      } else if (x > A[i]) { // not equal
        more_than_us++;
      }
    }
    answers[i] = max(less_than_us, more_than_us);
    processed.insert(A[i]);
  }

  for (int i = 0; i < n; i++) {
    cout << answers[i] << " ";
  }
  cout << "\n";

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}