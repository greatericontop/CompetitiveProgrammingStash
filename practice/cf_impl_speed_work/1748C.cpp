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
  vector<long> A(n);
  for (int i = 0; i < n; i++)  cin >> A[i];

  vector<int> indices;
  for (int i = 0; i < n; i++) {
    if (A[i] == 0)  indices.push_back(i);
  }
  indices.push_back(n);

  int ans = 0;

  for (int i = 0; i < (int)indices.size() - 1; i++) {
    int start = indices[i], end = indices[i+1];
    map<long, int> freq;
    long sum = 0;
        assert(A[start] == 0);
    for (int j = start; j < end; j++) {
      sum += A[j]; // includes 0 at beginning
      freq[sum]++;
    }
    int best_count = -1;
    for (const auto& [val, count] : freq) {
      best_count = max(best_count, count);
    }
    ans += best_count;
  }

  long sum = 0;
  for (int i = 0; i < indices[0]; i++) {
    sum += A[i];
    if (sum == 0)  ans++;
  }

  cout << ans << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
