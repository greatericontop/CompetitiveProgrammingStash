#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  if (n == 1) {
    cout << "1\n";
    return;
  }
  if (n == 2) {
    cout << "2 2\n";
    return;
  }
  if (n >= 3) {
    for (int i = 0; i < n; i++) {
      cout << "2 ";
    }
    cout << "\n";
  }
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}