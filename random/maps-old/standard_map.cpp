#include <bits/stdc++.h>
using namespace std;
#define long int64_t
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
#define FORI1(x) for (int i = 1; i <= (x); i++)




void solve() {
  int n, q;
  cin >> n >> q;
  map<int, int> data;
  FORI(n) {
    int k, v;
    cin >> k >> v;
    data[k] = v;
  }
  FORI(q) {
    int k;
    cin >> k;
    cout << data[k] << " ";
  }
  cout << "\n";
}




int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}
