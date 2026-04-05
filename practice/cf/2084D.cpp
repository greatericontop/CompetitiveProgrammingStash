#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  // Each number 0...x must appear m+1 times, with separation k

  if (n >= k*(m+1)) {

    int num_to_pack = n / (m+1);
    for (int i = 0; i < n; i++) {
      cout << i % num_to_pack << " \n"[i == n-1];
    }

  } else {

    // guaranteed n - m*k > 0
    int num_to_pack = n - m*k;
    for (int i = 0; i < n; i++) {
      cout << (i % k) % num_to_pack << " \n"[i == n - 1];
    }

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