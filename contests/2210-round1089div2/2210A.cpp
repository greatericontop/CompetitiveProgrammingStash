#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  for (int i = n; i >= 1; i--) {
    cout << i << " ";
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