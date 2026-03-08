#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n, m, L;
  cin >> n >> m >> L;
  vector<int> flashlight_times(n);
  for (int i = 0; i < n; i++) {
    cin >> flashlight_times[i];
  }
  sort(flashlight_times.begin(), flashlight_times.end());
  int flashlight_ptr = 0;

  // Stupid simulation is fast enough

  vector<int> animatronic_angers(m, 0);

  for (int second = 1; second <= L; second++) {
    sort(animatronic_angers.begin(), animatronic_angers.end(), greater<int>());
    // If we have 1 flash left, we want to maintain the 2nd most angry animatronic
    int to_increment_index = min(n - flashlight_ptr, m - 1);
    animatronic_angers[to_increment_index]++;


    // Flashlight
    if (flashlight_ptr < n && flashlight_times[flashlight_ptr] == second) {
      int max_index = 0;
      for (int i = 0; i < m; i++) {
        if (animatronic_angers[i] > animatronic_angers[max_index]) {
          max_index = i;
        }
      }
      animatronic_angers[max_index] = 0;

      flashlight_ptr++;
    }
  }

  cout << *max_element(animatronic_angers.begin(), animatronic_angers.end()) << "\n";

  // Time: L (M log M)  +  N log N

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}