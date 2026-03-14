#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  vector<int> board(n*n);
  for (int i = 0; i < n*n; i++) {
    cin >> board[i];
  }
  map<int, int> freq;
  for (int i = 0; i < n*n; i++) {
    freq[board[i]]++;
  }

  int highest_freq = 0;
  for (auto& [_, f] : freq) {
    highest_freq = max(highest_freq, f);
  }

  if (highest_freq <= n*(n-1)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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