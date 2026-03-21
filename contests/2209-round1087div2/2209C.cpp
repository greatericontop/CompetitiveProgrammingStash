#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  // Hidden array length 2n (at least length 4)

  for (int i = 5; i <= 2 * n; i += 2) {
    // 5 6, 7 8, ...
    cout << "? " << i << " " << (i + 1) << endl;
    int x;
    cin >> x;
    assert(x != -1);
    if (x == 1) {
      cout << "! " << i << endl;
      return;
    }
  }

  // [1 2 3 4], 3 queries left
  cout << "? 1 2" << endl;
  int x;
  cin >> x;
  assert(x != -1);
  if (x == 1) {
    cout << "! 1" << endl;
    return;
  }

  cout << "? 1 3" << endl;
  int y;
  cin >> y;
  assert(y != -1);
  if (y == 1) {
    cout << "! 1" << endl;
    return;
  }

  cout << "? 2 3" << endl;
  int z;
  cin >> z;
  assert(z != -1);
  if (z == 1) {
    cout << "! 2" << endl;
    return;
  }

  cout << "! 4" << endl;
  return;
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}