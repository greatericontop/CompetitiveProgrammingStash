#include <bits/stdc++.h>

using namespace std;

int n;
int main() {
  cin >> n;
  int pos = 0;
  for (int i=1; i<=n; i++) {
    cout << "?" << " " << i << " " << 1 << endl;
    cout.flush();
    int x; cin >> x;
    if (x) {
      pos = i;
      break;
    }
  }
  if (pos == 0) {
    cout << "! " << -1 << endl;
    cout.flush();
    return 0;
  }
  for (int i=1; i<n; i++) {
    int idx = (pos+i-1)%n+1;
    cout << "? " << idx << " " << i+1 << endl;
    cout.flush();
    int x; cin >> x;
    if (!x) {
      cout << "! " << -1 << endl;
      cout.flush();
      return 0;
    }
  }
  cout << "! " << pos - 1 << endl;
  cout.flush();
}