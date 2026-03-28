#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int x, y;
  cin >> x >> y;

  int S = abs(x - y);
  // Ans = # of factors of S
  // S = 2 ---> 1, 2 ---> ans of 2
  int factors = 0;
  for (int i = 1; i <= S; i++) {
    if (S % i == 0)  factors++;
  }
  if (S == 0)  factors = 1;

  cout << factors << "\n";
  for (int i = 0; i < x; i++) {
    cout << "1 ";
  }
  for (int i = 0; i < y; i++) {
    cout << "-1 ";
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