#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n;
  cin >> n;
  vector<int> A(n+1);
  vector<int> reverse(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    reverse[A[i]] = i;
  }

  int best = 0;
  set<int> elements;
  for (int i = 1; i <= n; i++) {
    // Number of elements 1...i that are >i
    // Remove i
    int index_of_i = reverse[i];
    if (elements.find(index_of_i) != elements.end()) {
      fprintf(stderr, "  removing %d\n", index_of_i);
      elements.erase(index_of_i);
    }
    elements.insert(i);
    fprintf(stderr, "i=%d, elements %d\n", i, (int)elements.size());
    best = max(best, (int)elements.size());
  }

  cout << best << "\n";

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}