#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  // Max

  string s1 = s;
  for (int i = 1; i < n-1; i++) {
    if (s1[i-1] == '1' && s1[i+1] == '1') {
      s1[i] = '1';
    }
  }
  int maximum = 0;
  for (char c : s1) {
    if (c == '1')  maximum++;
  }

  // Min

  string s2 = s1; // start from max string
  for (int i = 1; i < n-1; i++) {
    if (s2[i-1] == '1' && s2[i+1] == '1') {
      s2[i] = '0';
    }
  }
  int minimum = 0;
  for (char c : s2) {
    if (c == '1')  minimum++;
  }

  cout << minimum << ' ' << maximum << '\n';
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}