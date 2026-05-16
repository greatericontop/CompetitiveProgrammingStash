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











//#pragma GCC optimize("O3,Ofast,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define exp(x) (1 << (x))
void solve(vector<vector<vector<int>>>& masks) {
  int n, k;
  cin >> n >> k;
  string a, b;
  cin >> a >> b;
  set<char> a_chars_set;
  for (int i = 0; i < n; i++)  a_chars_set.insert(a[i]);
  vector<char> a_chars;
  for (char c : a_chars_set)  a_chars.push_back(c);

  long best = -1;
  for (int mask : masks[a_chars.size()][min(k, (int)a_chars_set.size())]) {
    set<char> subset;
    vector<bool> subset_flag(256, false);
    for (int i = 0; i < a_chars.size(); i++) {
      if (mask & exp(i)) {
        subset.insert(a_chars[i]);
        subset_flag[a_chars[i]] = true;
      }
    }
    long cur = 0;
    int last_ok_i = -1;
    for (int i = 0; i < n; i++) {
      bool in_subset = subset_flag[a[i]];
      if (a[i] == b[i] || in_subset) {
        if (last_ok_i == -1) {
          last_ok_i = i;
          cur += 1;
        } else {
          cur += i - last_ok_i + 1;
        }
      } else {
        last_ok_i = -1;
      }
    }
    best = max(best, cur);
    fprintf(stderr, "subset = %s, cur = %lld\n", string(subset.begin(), subset.end()).c_str(), cur);
  }

  cout << best << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<vector<vector<int>>> masks;
  masks.push_back({}); // dummy
  for (int sz = 1; sz <= 10; sz++) {
    auto our_masks = vector<vector<int>>(sz+1);
    for (int mask = 0; mask < exp(sz); mask++) {
      vector<int> subset;
      for (int i = 0; i < sz; i++) {
        if (mask & exp(i))  subset.push_back(i);
      }
      our_masks[subset.size()].push_back(mask);
    }
    masks.push_back(our_masks);
  }

  int t;
  cin >> t;
  while (t--)  solve(masks);
  return 0;
}
