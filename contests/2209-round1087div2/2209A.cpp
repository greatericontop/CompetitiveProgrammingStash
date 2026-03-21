#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  long skill, flipflop_count;
  cin >> skill >> flipflop_count;
  vector<long> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  sort(a.begin(), a.end());
  for (int i = 0; i < n; i++) {
    if (a[i] > skill) {
      break;
    }
    long difference = skill - a[i];
    long flips_used = min(difference, flipflop_count);
    flipflop_count -= flips_used;
    a[i] += flips_used;
    skill += a[i];
  }

  cout << skill << "\n";

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}