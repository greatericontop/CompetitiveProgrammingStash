#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
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
  vector<long> a(n);
  multiset<long> pos;
  multiset<long> neg;
  long zeros = 0;
  long mini = INT_MAX;
  long maxi = INT_MIN;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] > 0)  pos.insert(a[i]);
    else if (a[i] < 0)  neg.insert(-a[i]);
    else  zeros++;
    mini = min(mini, a[i]);
    maxi = max(maxi, a[i]);
  }

  if (pos.size() == 0 && neg.size() == 0) {
    cout << "No\n";
    return;
  }

  // keep min < prefix sum <= max
  vector<long> answers;
  long prefix_sum = 0;
  while (!pos.empty() || !neg.empty()) {
    assert(mini < prefix_sum && prefix_sum <= maxi);
    if (prefix_sum <= 0) {
      // take highest pos
      assert(!pos.empty());
      auto it = prev(pos.end());
      prefix_sum += *it;
      answers.push_back(*it);
      pos.erase(it);
    } else {
      // take highest neg
      assert(!neg.empty());
      auto it = prev(neg.end());
      prefix_sum -= *it;
      answers.push_back(-(*it));
      neg.erase(it);
    }
  }

  assert(prefix_sum == 0);
  cout << "Yes\n";
  for (const auto& x : answers)  cout << x << " ";
  for (int i = 0; i < zeros; i++)  cout << "0 ";
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
