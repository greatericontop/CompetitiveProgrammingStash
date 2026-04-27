#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


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
  string s;
  cin >> s;
  int n = (int)s.size();
  long pos_raw;
  cin >> pos_raw;
  pos_raw--;

  int k = 0;
  long pos = pos_raw;
  while (pos >= n-k) {
    pos -= (n-k);
    k++;
  }
  //fprintf(stderr, "string %d, pos %lld\n", k, pos);
  //OK

  string result;
  // perform k deletions
  for (int i = 0; i < n; i++) {
    // add s[i] to result
    // deletions
    while (!result.empty() && result.back() > s[i] && k > 0) {
      result.pop_back();
      k--;
    }
    result.push_back(s[i]);
  }
  // delete from back once we reach the end of the sweep
  while (k > 0) {
    result.pop_back();
    k--;
  }

  fprintf(stderr, "result string after deletions: %s\n", result.c_str());

#ifdef GREATERIC_DEBUG
  cout << result[pos] << "\n";
#else
  cout << result[pos];
#endif
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  cout << "\n";
  return 0;
}
