#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld, ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif












void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  int ct0 = 0, ct1 = 0, ct2 = 0;
  set<int> zeros;
  set<int> ones;
  set<int> twos;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] == 0) {
      ct0++;
      zeros.insert(i);
    } else if (a[i] == 1) {
      ct1++;
      ones.insert(i);
    } else {
      ct2++;
      twos.insert(i);
    }
  }

  vector<pair<int, int>> operations;

  // move zeros at the end to the front block (0...ct0-1)
  for (int i = 0; i < ct0; i++) {
    if (a[i] == 0)  continue;
    if (a[i] == 1) {
      // directly swap with 0 at the end (billed to the 0)
      auto it = zeros.rbegin();
      assert(it != zeros.rend());
      int zero_pos = *it;
      assert(zero_pos >= ct0);
      operations.emplace_back(zero_pos, i);
      swap(a[zero_pos], a[i]);
      zeros.erase(zero_pos);
      zeros.insert(i);
      ones.erase(i);
      ones.insert(zero_pos);
    } else {
      // swap 2 with 1 at the end (billed to the 2), then swap 1 and 0
      auto it = ones.rbegin();
      assert(it != ones.rend());
      int one_pos = *it;
      assert(one_pos > i);
      operations.emplace_back(one_pos, i);
      swap(a[one_pos], a[i]);
      ones.erase(one_pos);
      ones.insert(i);

      auto it2 = zeros.rbegin();
      assert(it2 != zeros.rend());
      int zero_pos = *it2;
      assert(zero_pos >= ct0);
      operations.emplace_back(zero_pos, i);
      swap(a[zero_pos], a[i]);
      zeros.erase(zero_pos);
      zeros.insert(i);
      ones.erase(i);
      ones.insert(zero_pos);
    }
  }

  // now swap ones
  for (int i = ct0; i < ct0 + ct1; i++) {
    if (a[i] == 1) continue;
    assert(a[i] == 2);
    auto it = ones.rbegin();
    assert(it != ones.rend());
    int one_pos = *it;
    operations.emplace_back(one_pos, i);
    swap(a[one_pos], a[i]);
    ones.erase(one_pos);
    ones.insert(i);
  }

  cout << operations.size() << "\n";
  for (const auto& p : operations) {
    cout << p.first+1 << " " << p.second+1 << "\n";
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
